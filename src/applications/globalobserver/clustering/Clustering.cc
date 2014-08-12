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
      ev << "Notification from: "<< id << endl;
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
   EV << globalNodeTable.info() << endl;
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
Clustering::
computeNeighborhood(uint32_t nodeID)
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

