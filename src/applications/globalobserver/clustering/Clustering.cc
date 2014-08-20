#include "Clustering.h"

Define_Module(Clustering);

Clustering::Clustering()
{
   hops = 0;
   range = 0;
   update = NULL;
   updateDelay = 0.0;
   receivedMessages = 0;
   criterion = " ";
   isRoleListInitialized = false;
}

Clustering::~Clustering(){}

void
Clustering::initialize()
{
   hops = (uint8_t)par("hops");
   range = (uint8_t)par("range");
   updateDelay = par("updateDelay");
   criterion = par("criterion").stringValue();
   update = new cMessage;
   scheduleAt(simTime()+updateDelay, update);
}

void
Clustering::handleMessage(cMessage* msg)
{
   if(msg->isSelfMessage())
   {
      if(receivedMessages == 0)
      {
         delete msg;
         endSimulation();
      }
      else
         receivedMessages = 0;
      updateTable();
      scheduleAt(simTime()+1, msg);
   }
   else
      updateTable(msg);
}

void
Clustering::updateTable(cMessage* msg)
{
   Notification* data = 
   check_and_cast<Notification*>(msg);
   uint32_t id = data->getSource();
   globalNodeTable.setPosition(id, data->getPosition());
   globalNodeTable.setPauseTime(id, data->getPauseTime());
   globalNodeTable.
   setMotionTime(id, data->getMotionTime());
   globalNodeTable.setSpeed(id, data->getSpeed());
   globalNodeTable.
   setFlightLength(id, data->getFlightLength());
   receivedMessages++;
   delete msg;
}

void
Clustering::updateTable()
{
   computeNeighborhood();
   if(!isRoleListInitialized)
   {
      initializeRoleList();
      if(ev.isGUI())
         changeIconColor();
   }
   else
      organizeClusters();
   makeClusters();
   if(ev.isGUI())
      changeIconColor();

   for(auto pair : globalNodeTable)
      ev << globalNodeTable.info(pair.first) << endl;
}

void
Clustering::organizeClusters()
{
   organizeLeaders();
   if(ev.isGUI())
      changeIconColor();
   organizeClusteredNodes();
   if(ev.isGUI())
         changeIconColor();
}

void
Clustering::
organizeLeaders()
{
   std::set<uint32_t>* invalid =
   new std::set<uint32_t>;
   std::set<uint32_t>* valid =
   new std::set<uint32_t>;
   const rolep_bag* roleList =
   globalNodeTable.accessRoleList();
   const Neighborhood* leaderNeighborhood;
   const Role* neighborRole;
   uint32_t leaderID;
   auto leaderRange = roleList->equalRange(Role::LEADER);
   auto it = leaderRange.first;
   bool isLeaderInvalid = false;
   do
   {
      leaderID = it->key();
      leaderNeighborhood =
      globalNodeTable.getState(leaderID).getKHop();
      if(leaderNeighborhood->size() == 0)
      {
         if(invalid->empty())
            invalid->insert(leaderID);
         else if(invalid->find(leaderID) != invalid->end())
            invalid->insert(leaderID);
         it++;
         continue;
      }
      for(auto& neighborID : *leaderNeighborhood)
      {
         neighborRole =
         globalNodeTable.getState(neighborID).getRole();  
         if(*neighborRole == Role::LEADER)
         {
            if(invalid->empty())
               invalid->insert(leaderID);
            else if(invalid->find(leaderID) != 
                    invalid->end())
               invalid->insert(leaderID);
            isLeaderInvalid = true;
         }
      }
      if(isLeaderInvalid)
      {
         if(invalid->empty())
            invalid->insert(leaderID);
         else if(invalid->find(leaderID) != 
                 invalid->end())
            invalid->insert(leaderID);
         isLeaderInvalid = false;
      }
      else
      {
         if(valid->empty())
            valid->insert(leaderID);
         else if(valid->find(leaderID) != 
                 valid->end())
            valid->insert(leaderID);
      }
      it++;
   }while(it != leaderRange.second);
   ev << "invalid leaders: ";
   for(auto& id : *invalid)
      ev << (int)id << ' ';
   ev << endl;
   ev << "valid leaders: ";
   for(auto& id : *valid)
      ev << (int)id << ' ';
   ev << endl;
   if(!invalid->empty())
      for(auto& id : *invalid)
      {
         ev << "unclustering leader " << id << endl;
         getRidOf(id);
      }
   if(!valid->empty())
      for(auto& id : *valid)
         makeCluster(id);
   delete invalid;
   delete valid;
}

void
Clustering::organizeClusteredNodes()
{
   const rolep_bag* roleList =
   globalNodeTable.accessRoleList();
   uint32_t clusteredNodeID;
   std::set<uint32_t> invalidClusteredNodes;
   auto clusteredNodeRange =
   roleList->equalRange(Role::CLUSTERED);
   auto leaderRange =
   roleList->equalRange(Role::LEADER);
   bool isRoleValid = false;
   ev << "Clustered nodes:" << endl;
   for(auto it =  clusteredNodeRange.first;
            it != clusteredNodeRange.second;
            it ++)
      ev << "ID: " << it->key() << ' '
         << "Role: " << it->value() << endl;
   ev << "Leaders:" << endl;
   for(auto it = leaderRange.first;
            it != leaderRange.second;
            it ++)
      ev << "ID: " << it->key() << ' '
         << "Role: " << it->value() << endl;
   ev << "Finding invalid clustered nodes" << endl;
   for(auto it =  clusteredNodeRange.first;
            it != clusteredNodeRange.second;
            it ++)
   {
      clusteredNodeID = it->key();
      const Neighborhood* vicinity =
      globalNodeTable.getState(clusteredNodeID).
      getKHop();
      ev << "Clustered node ID: " << clusteredNodeID << ' '
         << "Neighborhood: " << vicinity->info()
         << endl;
      for(auto& neighbor : *vicinity)
      {
         const Role* neighborRole =
         globalNodeTable.getState(neighbor).getRole();
         if(*neighborRole == Role::LEADER)
         {
            ev << "Valid clustered node: "
               << clusteredNodeID << endl;
            isRoleValid = true;
            break;
         }
      }
      if(!isRoleValid)
      {
         ev << "Invalid clustered node: "
            << clusteredNodeID << endl;
         invalidClusteredNodes.insert(clusteredNodeID);
      }
      else
         isRoleValid = false;
   }
   for(auto& id : invalidClusteredNodes)
      globalNodeTable.setRole(id, Role::UNCLUSTERED);
}

void
Clustering::makeClusters()
{
   std::pair<bool,uint32_t> leader;
   do
   {
      leader = getLeader();
      if(leader.first)
         makeCluster(leader.second);
   }while(leader.first);
}

std::pair<bool,uint32_t>
Clustering::getLeader()
{
   std::pair<bool,uint32_t> leader;
   if(criterion == "degree")
      leader = getLeaderByDegree();
   return leader;
}

//TODO: The UID must be considered to break ties
std::pair<bool,uint32_t>
Clustering::getLeaderByDegree()
{
   uint32_t leaderID;
   bool isLeaderInitialized = false;
   const uint32_t* tempID = NULL;
   uint8_t maxDegree = 0, degree;
   const rolep_bag* roleList =
         globalNodeTable.accessRoleList();
   for(auto& pair : *roleList)
      if(pair.value() == Role::UNCLUSTERED)
      {
         degree = globalNodeTable.getState(pair.key()).
                  getOneHop()->size();
         tempID = globalNodeTable.getState(pair.key()).
                  getUID();
         if(isLeaderInitialized)
         {
            if(degree == maxDegree && *tempID < leaderID)
               leaderID = *tempID;
            else if(degree > maxDegree)
            {
               maxDegree = degree;
               leaderID = *tempID;
            }
         }
         else if(degree > maxDegree)
         {
            maxDegree = degree;
            leaderID = *tempID;
            isLeaderInitialized = true;
         }
      }
   return std::make_pair(isLeaderInitialized, leaderID);
}

void
Clustering::initializeRoleList()
{
   const uint32_t* uid;
   for(auto& pair : globalNodeTable)
   {
      uid = pair.second.getUID();
      if(uid)
         globalNodeTable.setRole(*uid, Role::UNCLUSTERED);
   }
   isRoleListInitialized = true;
}

void
Clustering::makeCluster(uint32_t leaderID)
{
   const Neighborhood* cluster;
   //sets role LEADER
   globalNodeTable.setRole(leaderID, Role::LEADER);
   //sets cid using the CID leader ID
   globalNodeTable.setCid(leaderID, leaderID);
   //gets the k-hop neighborhood of the leader
   cluster = globalNodeTable.
             getState(leaderID).getKHop();
   //clusters all nodes that belongs to the k-hop
   //neighborhood of the leader. neighbor is the UID of
   //each node in the k-hop neighborhood of the leader
   for(auto& neighbor : *cluster)
      if(*globalNodeTable.getState(neighbor).getRole() == 
         Role::UNCLUSTERED)
      {
         //sets to neighbor the role CLUSTERED
         globalNodeTable.setRole(neighbor,Role::CLUSTERED);
         //sets to neighbor a CID equals the leader ID
         globalNodeTable.setCid(neighbor, leaderID);
      }
}

void
Clustering::getRidOf(uint32_t leaderID)
{
   const Neighborhood* cluster;
   globalNodeTable.setCid(leaderID, 0);
   globalNodeTable.setRole(leaderID, Role::UNCLUSTERED);
   //gets the k-hop neighborhood of the ex-leader
   cluster = globalNodeTable.
             getState(leaderID).getKHop();
   //unclusters all nodes that belongs to the k-hop
   //neighborhood of the ex-leader. neighbor is the UID of
   //each node in the k-hop neighborhood of the ex-leader
   for(auto& neighbor : *cluster)
      if(*globalNodeTable.getState(neighbor).getCid() == 
         leaderID)
      {
         //sets to neighbor the role CLUSTERED
         globalNodeTable.
         setRole(neighbor,Role::UNCLUSTERED);
         //neighbor CID equals the leader ID
         globalNodeTable.setCid(neighbor, 0);
      }
}

void
Clustering::changeIconColor()
{
   cModule* host;
   const uint32_t* index;
   for(auto& pair : globalNodeTable)
   {
      index = pair.second.getUID();//first?
      host = simulation.
             getSystemModule()->
             getSubmodule("host", *index);
      if(host)
      {
         cDisplayString& displayStr = 
         host->getDisplayString();
         const Role* role =
         globalNodeTable.getState(*index).getRole();
         if(*role == Role::LEADER)
            displayStr.
            parse("i=device/pocketpc_s,blue");
         else if (*role == Role::CLUSTERED)
            displayStr.
            parse("i=device/pocketpc_s,yellow");
         else if (*role == Role::GATEWAY)
            displayStr.
            parse("i=device/pocketpc_s,green");
         else
            displayStr.
            parse("i=device/pocketpc_s");
      }
   }
}

void
Clustering::computeNeighborhood()
{
   Neighborhood oneHopVicinity, kHopVicinity;
   uint32_t tempID;
   //Computes one hop neighborhood for all nodes
   for(auto& pair: globalNodeTable)
   {
      tempID = *(pair.second.getUID());
      oneHopVicinity = computeNeighborhood(tempID);
      globalNodeTable.
      setOneHopNeighborhood(tempID, oneHopVicinity);
   }
   //Computes k hop neighborhood for all nodes
   for(auto& pair: globalNodeTable)
   {
      tempID = *(pair.second.getUID());
      kHopVicinity = computeNeighborhood(tempID, hops);
      globalNodeTable.setKHopNeighborhood
      (tempID, kHopVicinity);
   }
}

Neighborhood
Clustering::computeNeighborhood(uint32_t nodeID)
{
   Neighborhood n;
   //Quick access to the node data
   const Coord* mypos = 
   globalNodeTable.getState(nodeID).getPosition();
   
   for(auto& pair : globalNodeTable)
   {
      const Coord* neighbor_pos = 
      pair.second.getPosition();
      const uint32_t* neighborID = pair.second.getUID();
      if
      (
         nodeID != *neighborID &&
         mypos->distance(*neighbor_pos) < range
      )
         n.insert(*neighborID);
   }
   return n;
}

//k is the number of hops
Neighborhood
Clustering::computeNeighborhood(uint32_t nodeID, uint8_t k)
{
   Neighborhood n;
   //get the neighborhood of the node with ID = nodeID
   n = *globalNodeTable.getState(nodeID).getOneHop();
   if(k>1)
      for(auto& neighbor : n)//for each neighbor in n
         n += computeNeighborhood(neighbor, k-1);
   n.erase(nodeID);
   return n;
}
