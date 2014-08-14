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
   {
      Notification* data = 
      check_and_cast<Notification*>(msg);
      uint32_t id = data->getSource();
      globalNodeTable.
      setPosition(id, data->getPosition());
      globalNodeTable.
      setPauseTime(id, data->getPauseTime());
      globalNodeTable.
      setMotionTime(id, data->getMotionTime());
      globalNodeTable.setSpeed(id, data->getSpeed());
      globalNodeTable.
      setFlightLength(id, data->getFlightLength());
      receivedMessages++;
      delete msg;
   }
}

void
Clustering::updateTable()
{
   computeNeighborhood();
   clustering();
   ev << globalNodeTable.info();
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

void
Clustering::clustering()
{
   const uint32_t* leaderID;
   if(isRoleListInitialized)
      initializeRoleList();
   do
   {
      leaderID = getLeader();
      if (leaderID)
      {
         makeCluster(*leaderID);
         ev << "Leader ID: " << (int)*leaderID << endl;
      }
   }while(leaderID);
   if(ev.isGUI())
      changeIconColor();
}

const uint32_t*
Clustering::getLeader()
{
   const uint32_t* leaderID;
   if(criterion == "degree")
      leaderID = getLeaderByDegree();
   return leaderID;
}

//TODO: The UID must be considered to break ties
const uint32_t*
Clustering::getLeaderByDegree()
{
   const uint32_t* leaderID = NULL;
   uint8_t maxDegree = 0;
   for(auto& pair: globalNodeTable)
   {
      if(*pair.second.getRole() == Role::UNCLUSTERED)
      {
         auto degree = pair.second.getOneHopIterator().
                       second->value().size();
         if(degree > maxDegree)
         {
            leaderID = pair.second.getUID();
            maxDegree = degree;
         }
      }
   }
   return leaderID;
}

void
Clustering::initializeRoleList()
{
   for(auto& pair : globalNodeTable)
   {
      auto uid = pair.second.getUID();
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
         cDisplayString& displayStr = host->
                                         getDisplayString();
         const Role* role = globalNodeTable.
                            getState(*index).getRole();
         if(*role == Role::LEADER)
            displayStr.
            parse("i=device/pocketpc_s,blue");
         else if (*role == Role::CLUSTERED)
            displayStr.
            parse("i=device/pocketpc_s,gold");
      }
   }
}
