#ifndef IGLOBAL_OBSERVER_H
#define IGLOBAL_OBSERVER_H
#include <omnetpp.h>
#include <cstdint>
#include "INETDefs.h"
#include "neighborhood_p.h"


/**
 * @brief Abstract base class defining the public interface
 * that must be provided by all global observer modules.
 *
 * @author Adán G. Medrano-Chávez
 */
class INET_API IGlobalObserver: public cSimpleModule
{
   protected:
      //coberture range of a node
      uint8_t range;
   public:
      virtual ~IGlobalObserver() {}

    /** @brief Returns the one-hop neighborhood of a node
     *  in a pair <id,neighborhood>.
     *  Their parameters are the ID of the node whose
     *  neighborhood must be computed and range is the
     *  coberture range of the mobile host. 
     */
   virtual Neighborhood
   computeNeighborhood(uint32_t nodeID) = 0; 
};


#endif
