#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include "node_state.h"

//TODO: implement a Table that be able to insert bags,
//regardless their type. It means a generic bag is needed

class Table
{
   protected:
      coordp_bag position_list;
      doublep_bag speed_list;
      doublep_bag flight_length_list;
      simtimep_bag pause_time_list;
      simtimep_bag motion_time_list;
      neighborhoodp_bag one_hop_neighborhood_list;
      neighborhoodp_bag k_hop_neighborhood_list;
      rolep_bag role_list;
      uint32p_bag cid_list;
      std::unordered_map<uint32_t,node_state> table;
   public:
      Table(); //default constructor
      virtual ~Table(); //default destructor
      //**************** Table iterators *****************/
      typedef std::unordered_map<uint32_t,node_state>::
              iterator iterator;
      typedef std::unordered_map<uint32_t,node_state>::
              const_iterator const_iterator;
      //Methods to set the node state. The explained
      //procedure of setter methods is detailed in
      //the setPosition method
      virtual void setPosition(uint32_t id, Coord p);
      virtual void setSpeed(uint32_t id, double s);
      virtual void setFlightLength(uint32_t id, double f);
      virtual void setPauseTime(uint32_t id, simtime_t p);
      virtual void setMotionTime(uint32_t id, simtime_t m);
      virtual void
              setOneHopNeighborhood
              (uint32_t id, Neighborhood n);
      virtual void
              setKHopNeighborhood
              (uint32_t id, Neighborhood n);
      virtual void setRole(uint32_t id, Role r);
      virtual void setCid(uint32_t id, uint32_t c);

      virtual void setState(uint32_t id, node_state s);
      //method to get the attributes of a node, if the
      //state does not exist, then a empty state is
      //returned
      virtual node_state getState(uint32_t id);
      //methods to get the value of the
      //begin and the end of each list
      virtual const coord_p* getPositionListMin() const;
      virtual const coord_p* getPositionListMax() const;
      virtual const double_p* getSpeedListMin() const;
      virtual const double_p* getSpeedListMax() const;
      virtual const double_p*
              getFlightLengthListMin() const;
      virtual const double_p*
              getFlightLengthListMax() const;
      virtual const simtime_p*
              getPauseTimeListMin() const;
      virtual const simtime_p*
              getPauseTimeListMax() const;
      virtual const simtime_p*
              getMotionTimeListMin() const;
      virtual const simtime_p*
              getMotionTimeListMax() const;
      virtual const neighborhood_p*
              getOneHopNeighborhoodListMin() const;
      virtual const neighborhood_p*
              getOneHopNeighborhoodListMax() const;
      virtual const neighborhood_p*
              getKHopNeighborhoodListMin() const;
      virtual const neighborhood_p*
              getKHopNeighborhoodListMax() const;
      virtual const role_p*
              getRoleListMin() const;
      virtual const role_p*
              getRoleListMax() const;
      virtual const uint32p*
              getCidListMin() const;
      virtual const uint32p*
              getCidListMax() const;
      //methods to only-read the lists
      virtual const coordp_bag* accessPositionList() const;
      virtual const doublep_bag* accessSpeedList() const;
      virtual const doublep_bag*
              accessFlightLengthList() const;
      virtual const simtimep_bag*
              accessPauseTimeList() const;
      virtual const simtimep_bag*
              accessMotionTimeList() const;
      virtual const neighborhoodp_bag*
              accessOneHopNeighborhoodList() const;
      virtual const neighborhoodp_bag*
              accessKHopNeighborhoodList() const;
      virtual const rolep_bag*
              accessRoleList() const;
      virtual const uint32_t*
              accessCidList() const;
      //methods to access and to manage the table
      virtual unsigned int size() const;
      virtual void erase(uint32_t id);
      virtual void clear();
      virtual iterator begin();
      virtual iterator end();
      virtual std::string info();
};
#endif
