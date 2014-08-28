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
   leaderChurn = registerSignal("changes");
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
   uint8_t changes;

   emit(numberOfLeaders, leaderSetSize);
   ev << "Number of leaders: "
      << (int)leaderSetSize << endl;

   for(auto& pair : leaderTable)
   {
      simtime_t leadershipPeriod =
      pair.second.second - pair.second.first;
      if(leadershipPeriod > 0)
      {
         emit(leadershipTime,leadershipPeriod);
         leadersToBeErased.push_back(pair.first);
      }
   }
   ev << "Leadership time:" << '\n'
      << leaderTable.info();
   for(auto& id : leadersToBeErased)
      leaderTable.erase(id);
   changes = leaderTable.getChanges();
   emit(leaderChurn, changes);
   ev << "Leadership changes: " << (int)changes << endl;
   leaderTable.resetChanges();   
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
      initializeRoleList();
   else
      organizeClusters();
   makeClusters();
   if(ev.isGUI())
      changeIconColor();
   printClusters();
}

void
Clustering::organizeClusters()
{  
   organizeClusteredNodes();
   organizeLeaders();
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
   if(!invalid->empty())
      for(auto& id : *invalid)
         getRidOf(id);
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
   for(auto it =  clusteredNodeRange.first;
            it != clusteredNodeRange.second;
            it ++)
   {
      clusteredNodeID = it->key();
      auto myleader = getLeaderOf(clusteredNodeID);
      if(myleader.first == 65535)
         invalidClusteredNodes.insert(clusteredNodeID);
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
   //sets cid using the CID leader ID plus 1000
   globalNodeTable.setCid(leaderID, leaderID+1000);
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
         setCid(neighbor.first, leaderID+1000);
      }
      else if(*globalNodeTable.getState(neighbor.first).
              getRole() == Role::CLUSTERED)
      {
         auto leaderOfMyNeighbor = 
         getLeaderOf(neighbor.first);
         if(neighbor.second < leaderOfMyNeighbor.second)
         //sets to neighbor a CID equals the leader ID
            globalNodeTable.
            setCid(neighbor.first, leaderID+1000);
         else if
         (neighbor.second == leaderOfMyNeighbor.second &&
          leaderID < leaderOfMyNeighbor.first)
            //sets to neighbor a CID equals the leader ID
            globalNodeTable.
            setCid(neighbor.first, leaderID+1000);
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
         leaderID+1000)
      {
         //sets to neighbor the role CLUSTERED
         globalNodeTable.
         setRole(neighbor.first,Role::UNCLUSTERED);
         //neighbor CID equals 0
         globalNodeTable.setCid(neighbor.first, 0);
      }
   leaderTable.setEndTime(leaderID,simTime());
}

Neighborhood::Neighbor
Clustering::getLeaderOf(uint32_t id)
{
   Neighborhood::Neighbor leader(65535,255);
   const Neighborhood* vicinity =
   globalNodeTable.getState(id).getKHop();
   uint32_t myleader =
   *globalNodeTable.getState(id).getCid() - 1000;
   if(vicinity->find(myleader) != vicinity->end())
   {
      leader.first = myleader;
      leader.second = vicinity->value(myleader);
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
      kHop.insert(nodeID, 0);
   }
   oneHop = globalNodeTable.getState(nodeID).getOneHop();
   for(auto& neighbor : *oneHop)
      if(kHop.find(neighbor.first) == kHop.end() ||
         hops-k+1 < kHop.value(neighbor.first))
         kHop.insert(neighbor.first, hops-k+1);
   if(k > 1)
      for(auto& neighbor : *oneHop)
         kHop += computeNeighborhood(neighbor.first, k-1);
   if(k == hops)
      kHop.erase(nodeID);
   return kHop;
}

void
Clustering::changeIconColor()
{
   cModule* host;
   const rolep_bag* roleList =
   globalNodeTable.accessRoleList();
   uint32_t nodeID, leaderID;
   std::string iconAttr, color;
   static std::unordered_map<uint32_t,std::string>
   clusterColorTable;

   //erases all staled datum
   if(!clusterColorTable.empty())
      for(auto& leader : clusterColorTable)
         if(leaderTable.find(leader.first) ==
            leaderTable.end())
            clusterColorTable.erase(leaderID);

   auto leaderRange =
   roleList->equalRange(Role::LEADER);
   for(auto it =  leaderRange.first;
            it != leaderRange.second;
            it ++)
   {
      leaderID = it->key();
      host = simulation.
             getSystemModule()->
             getSubmodule("host", leaderID);
      //contains icon attributes of a host
      cDisplayString& displayStr =
      host->getDisplayString();
      //all new leader is inserted here
      if(clusterColorTable.find(leaderID) ==
         clusterColorTable.end())
      {
         color = pickRandomColor(); //color
         clusterColorTable[leaderID] = color;
      }
      else
         color = clusterColorTable[leaderID];
      iconAttr = "i=device/pocketpc_s,"; //image
      iconAttr += color;
      iconAttr += ",50"; //brightness
      displayStr.parse(iconAttr.c_str());
   }

   auto clusteredNodeRange =
   roleList->equalRange(Role::CLUSTERED);
   for(auto it =  clusteredNodeRange.first;
            it != clusteredNodeRange.second;
            it++)
   {
      nodeID = it->key();
      leaderID = getLeaderOf(nodeID).first;
      host = simulation.
             getSystemModule()->
             getSubmodule("host", nodeID);
      //contains icon attributes of a host
      cDisplayString& displayStr =
      host->getDisplayString();
      iconAttr = "i=device/pocketpc_vs,"; //image
      iconAttr += clusterColorTable[leaderID];//color
      iconAttr += ",30"; //brightness
      displayStr.parse(iconAttr.c_str());
   }

   auto unclusteredNodeRange =
   roleList->equalRange(Role::UNCLUSTERED);
   for(auto it =  unclusteredNodeRange.first;
            it != unclusteredNodeRange.second;
            it ++)
   {
      nodeID = it->key();
      host = simulation.
             getSystemModule()->
             getSubmodule("host", nodeID);
      //contains icon attributes of a host
      cDisplayString& displayStr =
      host->getDisplayString();
      displayStr.parse("i=device/pocketpc_vs");
   }
}

std::string
Clustering::pickRandomColor()
{
   std::string htmlColor;
   uint8_t ruletteValue = intuniform(1,14);
   switch(ruletteValue)
   {
      case 1:
         htmlColor = "#FFFFFF";  //Black
         break;
      case 2:
         htmlColor = "#000000";  //White
         break;
      case 3:
         htmlColor = "#FF0000";  //Red
         break;
      case 4:
         htmlColor = "#800000";  //Maroon
         break;
      case 5:
         htmlColor = "#FFFF00";  //Yellow
         break;
      case 6:
         htmlColor = "#808000";  //Olive
         break;
      case 7:
         htmlColor = "#00FF00";  //Lime
         break;
      case 8:
         htmlColor = "#008000";  //Green
         break;
      case 9:
         htmlColor = "#00FFFF";  //Aqua
         break;
      case 10:
         htmlColor = "#008080";  //Teal
         break;
      case 11:
         htmlColor = "#0000FF";  //Blue
         break;
      case 12:
         htmlColor = "#000080";  //Navy
         break;
      case 13:
         htmlColor = "#FF00FF";  //Fucsia
         break;
      default:
         htmlColor = "#000080";  //Purple
         break;
   }
   return htmlColor;
}

void
Clustering::printClusters()
{
   const uint32p_bag* cidList =
   globalNodeTable.accessCidList();
   const rolep_bag* roleList =
   globalNodeTable.accessRoleList();
   uint32_t leaderID;
   std::set<uint32_t> nodes;

   auto leaderRange = roleList->equalRange(Role::LEADER);

   for(auto it =  leaderRange.first;
            it != leaderRange.second;
            it++)
   {
      leaderID = it->key();
      ev << "Cluster " << (int)leaderID+1000 << ": ";
      auto clusteredNodeRange = 
      cidList->equalRange(leaderID+1000);
      for(auto it =  clusteredNodeRange.first;
               it != clusteredNodeRange.second;
               it ++)
         nodes.insert(it->key());
      for(auto& node : nodes)
         ev << (int)node << ' ';
      ev << endl;
      nodes.clear();
   }

   ev << "Unclustered nodes: ";
   auto unclusteredNodeRange =
   roleList->equalRange(Role::UNCLUSTERED);
   for(auto it =  unclusteredNodeRange.first;
            it != unclusteredNodeRange.second;
            it ++)
      nodes.insert(it->key());
   for(auto& node : nodes)
      ev << (int)node << ' ';
   ev << endl;
}

void
Clustering::printTable()
{
   ev << "Global node table contains: " << endl;
   for(auto& pair : globalNodeTable)
      ev << pair.second.info();
}
