#ifndef GLOBAL_DUMMY_H
#define GLOBAL_DUMMY_H

#include <omnetpp.h>
#include "notification_m.h"
#include "IGlobalObserver.h"

class INET_API GlobalDummy: public cSimpleModule
{
   protected:
      //Shows the ID of the sender when the simulation
      //is executed in the Tkenv user interface
      void handleMessage(cMessage* msg);
      //Does nothing
      virtual Neighborhood
      computeNeighborhood(uint32_t nodeID);
   public:
      GlobalDummy();
      ~GlobalDummy();
};

#endif
