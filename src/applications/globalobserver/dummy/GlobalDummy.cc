#include "GlobalDummy.h"

Define_Module(GlobalDummy);

GlobalDummy::
GlobalDummy(){}

GlobalDummy::
~GlobalDummy(){}

Neighborhood
GlobalDummy::computeNeighborhood(uint32_t nodeID)
{
   Neighborhood n;
   return n;
}

void GlobalDummy::
handleMessage(cMessage* msg)
{
   Notification* dataNode =
   check_and_cast<Notification*>(msg);
   std::string output =
   "Notification's been received from node ";
   output += std::to_string(dataNode->getSource());

   if (ev.isGUI())
      bubble(output.c_str());

   delete msg;
}
