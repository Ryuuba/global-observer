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
   numberOfLeaders = registerSignal("leaders");
   leadershipTime = registerSignal("leaderOff");
}

void
Clustering::handleMessage(cMessage* msg)
{
   if(msg->isSelfMessage())
   {
      if(receivedMessages == 0)
      {
         for(auto& pair : leaderTable)
         {
            if(pair.second.second == 0.0)
            {
               simtime_t leadershipPeriod =
               simTime() - pair.second.first;
               emit(leadershipTime, leadershipPeriod);
            }
         }
         std::cout << "leader table content:" 
                   << std::endl
                   << leaderTable.info() << std::endl;
         delete msg;
         endSimulation();
      }
      else
         receivedMessages = 0;
      updateTable();
      emitStatistics();
      scheduleAt(simTime()+1, msg);
   }
   else
      updateTable(msg);
}

void
Clustering::emitStatistics()
{
   auto roleList = globalNodeTable.accessRoleList();
   uint8_t leaderSetSize = roleList->count(Role::LEADER);
   std::list<uint32_t> leadersToBeErased;
   emit(numberOfLeaders, leaderSetSize);
   for(auto& pair : leaderTable)
   {
      simtime_t leadershipPeriod =
      pair.second.second - pair.second.first;
      if(leadershipPeriod < 0)
         continue;
      else
      {
         emit(leadershipTime,leadershipPeriod);
         leadersToBeErased.push_back(pair.first);
      }
   }
   for(auto& id : leadersToBeErased)
      leaderTable.erase(id);
   ev << "leader table content:" << '\n'
      << leaderTable.info() << endl;
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
   organizeClusteredNodes();
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
   ev << "computing invalid leaders . . ." << endl;
   ev << "list of leaders: ";
   for(auto it_i = leaderRange.first;
            it_i!=leaderRange.second; it_i++)
      ev << it_i->key() << ' ';
   ev << endl;
   do
   {
      leaderID = it->key();
      leaderNeighborhood =
      globalNodeTable.getState(leaderID).getKHop();
      ev << "Leader ID: " << leaderID << ' '
         << (int)hops << "-hop neighborhood: "
         << leaderNeighborhood->info() << endl;
      if(leaderNeighborhood->size() == 0)
      {
         if(invalid->empty())
            invalid->insert(leaderID);
         else if(invalid->find(leaderID) != invalid->end())
            invalid->insert(leaderID);
         it++;
         continue;
      }
      for(auto& neighbor : *leaderNeighborhood)
      {
         neighborRole =
         globalNodeTable.getState(neighbor.first).
         getRole();  
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
         else if(invalid->find(leaderID) == 
                 invalid->end())
            invalid->insert(leaderID);
         isLeaderInvalid = false;
      }
      else
      {
         if(valid->empty())
            valid->insert(leaderID);
         else if(valid->find(leaderID) == 
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
   bool isRoleValid = false;
 
   for(auto it =  clusteredNodeRange.first;
            it != clusteredNodeRange.second;
            it ++)
   {
      clusteredNodeID = it->key();
      const Neighborhood* myKVicinity =
      globalNodeTable.getState(clusteredNodeID).
      getKHop();
      const uint32* myleader =
      globalNodeTable.getState(clusteredNodeID).getCid();
      for(auto& neighbor : *myKVicinity)
      {
         if(neighbor.first == *myleader)
         {
            isRoleValid = true;
            break;
         }
      }
      if(!isRoleValid)
         invalidClusteredNodes.insert(clusteredNodeID);
      else
         isRoleValid = false;
   }
   for(auto& id : invalidClusteredNodes)
   {
      globalNodeTable.setRole(id, Role::UNCLUSTERED);
      globalNodeTable.setCid(id,0);
   }
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

void
Clustering::makeCluster(uint32_t leaderID)
{
   const Neighborhood* cluster;
   //sets role LEADER
   globalNodeTable.setRole(leaderID, Role::LEADER);
   //sets cid using the CID leader ID
   globalNodeTable.setCid(leaderID, leaderID);
   //store the leader in the leaderTable. The insertion
   //is only performed when the leader ID is not in the
   //leaderTable
   leaderTable.setStartTime(leaderID,simTime());
   //gets the k-hop neighborhood of the leader
   cluster = globalNodeTable.
             getState(leaderID).getKHop();
   //clusters all nodes that belongs to the k-hop
   //neighborhood of the leader. neighbor is the UID of
   //each node in the k-hop neighborhood of the leader
   for(auto& neighbor : *cluster)
   {
      if(*globalNodeTable.getState(neighbor.first).
         getRole() == Role::UNCLUSTERED)
      {
         //sets to neighbor the role CLUSTERED
         globalNodeTable.
         setRole(neighbor.first,Role::CLUSTERED);
         //sets to neighbor a CID equals the leader ID
         globalNodeTable.
         setCid(neighbor.first, leaderID);
      }
      else if(*globalNodeTable.getState(neighbor.first).
              getRole() == Role::CLUSTERED)
      {
         auto leaderOfMyNeighbor = 
         getLeaderOf(neighbor.first);
         if(neighbor.second < leaderOfMyNeighbor.second)
         {
         //sets to neighbor the role CLUSTERED
         globalNodeTable.
         setRole(neighbor.first,Role::CLUSTERED);
         //sets to neighbor a CID equals the leader ID
         globalNodeTable.
         setCid(neighbor.first, leaderID);
         }
         else if
         (neighbor.second == leaderOfMyNeighbor.second &&
          leaderID < leaderOfMyNeighbor.first)
         {
         //sets to neighbor the role CLUSTERED
         globalNodeTable.
         setRole(neighbor.first,Role::CLUSTERED);
         //sets to neighbor a CID equals the leader ID
         globalNodeTable.
         setCid(neighbor.first, leaderID);
         }
      }

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
      if(*globalNodeTable.
          getState(neighbor.first).getCid() == 
         leaderID)
      {
         //sets to neighbor the role CLUSTERED
         globalNodeTable.
         setRole(neighbor.first,Role::UNCLUSTERED);
         //neighbor CID equals the leader ID
         globalNodeTable.setCid(neighbor.first, 0);
      }
   leaderTable.setEndTime(leaderID,simTime());
}

Neighborhood::Neighbor
Clustering::getLeaderOf(uint32_t id)
{
   Neighborhood::Neighbor leader(0,0);
   const rolep_bag* roleList =
   globalNodeTable.accessRoleList();
   const Neighborhood* vicinity =
   globalNodeTable.getState(id).accessRoleList();
   auto leaderRange = roleList->equalRange(Role::LEADER);

   for(auto it = leaderRange.first;
            it != leaderRange.second;
            it ++)
      if(vicinity->find(it->key()) != vicinity->end())
      {
         leader.first = it->key();
         leader.second = vicinity->value(it->key());
         break;
      }
   return leader;
}

std::pair<bool,uint32_t>
Clustering::getLeader()
{
   std::pair<bool,uint32_t> leader;
   if(criterion == "degree")
      leader = getLeaderByDegree();
   else if(criterion == "k-hop")
      leader = getLeaderByKHopNeighborhood();
   return leader;
}

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

std::pair<bool,uint32_t>
Clustering::getLeaderByKHopNeighborhood()
{
   uint32_t leaderID;
   bool isLeaderInitialized = false;
   const uint32_t* tempID = NULL;
   uint8_t kHopMax = 0, kHopSize;
   const rolep_bag* roleList = 
   globalNodeTable.accessRoleList();

   for(auto& pair : *roleList)
      if(pair.value() == Role::UNCLUSTERED)
      {
         kHopSize = globalNodeTable.getState(pair.key()).
                     getKHop()->size();
         tempID = globalNodeTable.getState(pair.key()).
                  getUID();
         if(isLeaderInitialized)
         {
            if(kHopSize == kHopMax && *tempID < leaderID)
               leaderID = *tempID;
            else if(kHopSize > kHopMax)
            {
               kHopMax = kHopSize;
               leaderID = *tempID;
            }
         }
         else if(kHopSize > kHopMax)
         {
            kHopMax = kHopSize;
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
         mypos->distance(*neighbor_pos) <= range
      )
         n.insert(*neighborID, 1);
   }
   return n;
}

//k is the number of hops
Neighborhood
Clustering::
computeNeighborhood(uint32_t nodeID, uint8_t k)
{
   const Neighborhood* oneHop;
   static Neighborhood kHop;
   if(k == hops)
   {
      kHop.clear();
      kHop.insert(nodeID,0);
   }
   oneHop = globalNodeTable.getState(nodeID).getOneHop();
   for(auto& neighbor : *oneHop)
      if(kHop.find(neighbor.first) == kHop.end() ||
         hops-k+1 < kHop.value(neighbor.first))
         kHop.insert(neighbor.first, hops-k+1);
   if(k > 1)
      for(auto& neighbor : *oneHop)//for each neighbor in n
         kHop += computeNeighborhood(neighbor.first, k-1);
   if(k == hops)
      kHop.erase(nodeID);
   return kHop;
}
