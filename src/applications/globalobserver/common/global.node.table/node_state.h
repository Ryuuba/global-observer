#ifndef NODE_STATE_H
#define NODE_STATE_H
#include <utility>
#include "role.h"
#include "coordp_bag.h"
#include "doublep_bag.h"
#include "neighborhoodp_bag.h"
#include "rolep_bag.h"
#include "simtimep_bag.h"
#include "uint32p_bag.h"
#include "uint8p_bag.h"

class node_state
{
   protected:
      //Node state is integrated by iterators pointing to
      //pairs <id,value>. In the 2nd element is stored the
      //value corresponding to the position, pause-time,
      //motion time, speed, flight length, one-hop
      //neighborhood, k-hop'neighborhood, role, and cluster
      //ID of the node. Owing to use iterator, the state
      //also contains bool variable to determine whether a
      //iterator is set.
      //This class must be extended
      //to add more node attributes or it can be added to
      //this file

      uint32_t UID;
      bool isUidSet;
      coordp_bag::iterator position;
      bool isPositionSet;
      simtimep_bag::iterator pause_time;
      bool isDistanceSet;
      doublep_bag::iterator distance;
      bool isPauseTimeSet;
      simtimep_bag::iterator motion_time;
      bool isMotionTimeSet;
      doublep_bag::iterator speed;
      bool isSpeedSet;
      doublep_bag::iterator flight_length;
      bool isFlightLengthSet;
      neighborhoodp_bag::iterator one_hop;
      bool isOneHopSet;
      neighborhoodp_bag::iterator k_hop;
      bool isKHopSet;
      rolep_bag::iterator role;
      bool isRoleSet;
      uint32p_bag::iterator cid;
      bool isCidSet;
      uint8p_bag::iterator leader_hop;
      bool isLeaderHopSet;
   public:
      node_state();
      virtual ~node_state();
      /*************** Getter state methods **************/
      //They return a pointer to the specific value of a
      //node feature. If the corresponding iterator is
      //invalid, then these methods return a NULL pointer.
      //Note that pointers point to const value, so they
      //can be used to modify node attributes because they
      //are only-read.
      virtual const uint32_t* getUID() const;
      virtual const Coord* getPosition() const;
      virtual const double* getDistance() const;
      virtual const double* getSpeed() const;
      virtual const double* getFlightLength() const;
      virtual const simtime_t* getPauseTime() const;
      virtual const simtime_t* getMotionTime() const;
      virtual const Neighborhood* getOneHop() const;
      //virtual unsigned int* getDegree();
      virtual const Neighborhood* getKHop() const;
      //virtual unsigned int* getKHopSize();
      virtual const Role* getRole() const;
      virtual const uint32_t* getCid() const;
      virtual const uint8_t* getHopsToTheLeader() const;
      /************** Getter iterator methods ************/
      //They return pair of kind <bool, bag it>. The bool
      //value indicates if the iterator is valid or not.
      //Returning-a-pair strategy is used because iterators
      //cannot be initialized with a NULL value
      virtual std::pair<bool,coordp_bag::iterator>
              getPositionIterator();
      virtual std::pair<bool,doublep_bag::iterator>
              getDistanceIterator();
      virtual std::pair<bool,doublep_bag::iterator>
              getSpeedIterator();
      virtual std::pair<bool,doublep_bag::iterator>
              getFlightLengthIterator();
      virtual std::pair<bool,simtimep_bag::iterator>
              getPauseTimeIterator();
      virtual std::pair<bool,simtimep_bag::iterator>
              getMotionTimeIterator();
      virtual std::pair<bool,neighborhoodp_bag::iterator>
              getOneHopIterator();
      virtual std::pair<bool,neighborhoodp_bag::iterator>
              getKHopIterator();
      virtual std::pair<bool,rolep_bag::iterator>
              getRoleIterator();
      virtual std::pair<bool,uint32p_bag::iterator>
              getCidIterator();
      virtual std::pair<bool,uint8p_bag::iterator>
              getHopsToTheLeaderIterator();
      /****************** Setter methods *****************/
      //This methods receive iterator from bags as formal
      //arguments
      virtual void setUID(uint32_t id);
      virtual void setPosition(coordp_bag::iterator it);
      virtual void setDistance(doublep_bag::iterator it);
      virtual void setSpeed(doublep_bag::iterator it);
      virtual void
              setFlightLength(doublep_bag::iterator it);
      virtual void setPauseTime(simtimep_bag::iterator it);
      virtual void
      		  setMotionTime(simtimep_bag::iterator it);
      virtual void
              setOneHop(neighborhoodp_bag::iterator it);
      virtual void
              setKHop(neighborhoodp_bag::iterator it);
      virtual void setRole(rolep_bag::iterator it);
      virtual void setCid(uint32p_bag::iterator it);
      virtual void
              setHopsToTheLeader(uint8p_bag::iterator it);
      //This method prints the node-state content
      virtual std::string info();
};

#endif
