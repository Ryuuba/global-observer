#include "Table.h"

Table::Table(){}

Table::~Table(){}

void
Table::setPosition(uint32_t id, Coord p)
{
   //If ID corresponds to a new node then it inserts
   //a new empty state
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   //otherwise, if the iterator contained in the state
   //is initialized, then it erases from the position
   //list the corresponding item
   else if(table[id].getPositionIterator().first)
	{
	   //it gets the old iterator
      auto it = table[id].getPositionIterator().second;
      //it erases from the position list
   	position_list.erase(it);
   }
   //it inserts the new pair into the position list
   auto it = position_list.insert(id, p);
   //it updates the position list iterator
   table[id].setPosition(it);
}

void
Table::setDistance(uint32_t id, double d)
{
   //If ID corresponds to a new node then it inserts
   //a new empty state
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   //otherwise, if the iterator contained in the state
   //is initialized, then it erases from the position
   //list the corresponding item
   else if(table[id].getDistanceIterator().first)
	{
	   //it gets the old iterator
      auto it = table[id].getDistanceIterator().second;
      //it erases from the position list
   	distance_list.erase(it);
   }
   //it inserts the new pair into the position list
   auto it = distance_list.insert(id, d);
   //it updates the position list iterator
   table[id].setDistance(it);
}

void
Table::setSpeed(uint32_t id, double s)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getSpeedIterator().first)
	{
      auto it = table[id].getSpeedIterator().second;
   	speed_list.erase(it);
   }
   auto it = speed_list.insert(id, s);
   table[id].setSpeed(it);
}

void
Table::setFlightLength(uint32_t id, double f)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getFlightLengthIterator().first)
	{
      auto it = table[id].getFlightLengthIterator().second;
   	flight_length_list.erase(it);
   }
   auto it = flight_length_list.insert(id, f);
   table[id].setFlightLength(it);
}

void
Table::setPauseTime(uint32_t id, simtime_t p)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getPauseTimeIterator().first)
	{
      auto it = table[id].getPauseTimeIterator().second;
   	pause_time_list.erase(it);
   }
   auto it = pause_time_list.insert(id, p);
   table[id].setPauseTime(it);
}

void
Table::setMotionTime(uint32_t id, simtime_t m)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getMotionTimeIterator().first)
	{
      auto it = table[id].getMotionTimeIterator().second;
   	motion_time_list.erase(it);
   }
   auto it = motion_time_list.insert(id, m);
   table[id].setMotionTime(it);
}

void
Table::setOneHopNeighborhood(uint32_t id, Neighborhood n)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getOneHopIterator().first)
	{
      auto it = table[id].getOneHopIterator().second;
   	one_hop_neighborhood_list.erase(it);
   }
   auto it = one_hop_neighborhood_list.insert(id, n);
   table[id].setOneHop(it);
}

void
Table::setKHopNeighborhood(uint32_t id, Neighborhood n)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getKHopIterator().first)
	{
      auto it = table[id].getKHopIterator().second;
   	k_hop_neighborhood_list.erase(it);
   }
   auto it = k_hop_neighborhood_list.insert(id, n);
   table[id].setKHop(it);
}

void
Table::setRole(uint32_t id, Role r)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getRoleIterator().first)
	{
      auto it = table[id].getRoleIterator().second;
   	role_list.erase(it);
   }
   auto it = role_list.insert(id, r);
   table[id].setRole(it);
}

void
Table::setCid(uint32_t id, uint32_t c)
{
   if(table.find(id) == table.end())
   {
		node_state state;
		state.setUID(id);
      table[id] = state;
   }
   else if(table[id].getCidIterator().first)
	{
      auto it = table[id].getCidIterator().second;
   	cid_list.erase(it);
   }
   auto it = cid_list.insert(id, c);
   table[id].setCid(it);
}

void
Table::setState(uint32_t id, node_state s)
{
   table[id] = s;
}

node_state
Table::getState(uint32_t id)
{
   node_state temp_state;
   if(table.find(id) != table.end())
      temp_state = table[id];
   return temp_state;
}

const coord_p*
Table::getPositionListMin() const
{
   const coord_p* position = NULL;
   if(!position_list.empty())
      position = &(*position_list.begin());
   return position;
}

const coord_p*
Table::getPositionListMax() const
{
   const coord_p* position = NULL;
   if(!position_list.empty())
      position = &(*position_list.max());
   return position;

}

const double_p*
Table::getDistanceListMin() const
{
   const double_p* distance = NULL;
   if(!distance_list.empty())
      distance = &(*distance_list.begin());
   return distance;
}

const double_p*
Table::getDistanceListMax() const
{
   const double_p* distance = NULL;
   if(!distance_list.empty())
      distance = &(*distance_list.max());
   return distance;
}

const double_p*
Table::getSpeedListMin() const
{
   const double_p* speed = NULL;
   if(!speed_list.empty())
      speed = &(*speed_list.begin());
   return speed;
}

const double_p*
Table::getSpeedListMax() const
{
   const double_p* speed = NULL;
   if(!speed_list.empty())
      speed = &(*speed_list.max());
   return speed;
}

const double_p*
Table::getFlightLengthListMin() const
{
   const double_p* flightLength = NULL;
   if(!flight_length_list.empty())
      flightLength = &(*flight_length_list.begin());
   return flightLength;
}

const double_p*
Table::getFlightLengthListMax() const
{
   const double_p* flightLength = NULL;
   if(!flight_length_list.empty())
      flightLength = &(*flight_length_list.max());
   return flightLength;
}

const simtime_p*
Table::getPauseTimeListMin() const
{
   const simtime_p* pauseTime = NULL;
   if(!pause_time_list.empty())
      pauseTime = &(*pause_time_list.begin());
   return pauseTime;
}

const simtime_p*
Table::getPauseTimeListMax() const
{
   const simtime_p* pauseTime = NULL;
   if(!pause_time_list.empty())
      pauseTime = &(*pause_time_list.max());
   return pauseTime;
}

const simtime_p*
Table::getMotionTimeListMin() const
{
   const simtime_p* motionTime = NULL;
   if(!motion_time_list.empty())
      motionTime = &(*motion_time_list.begin());
   return motionTime;
}

const simtime_p*
Table::getMotionTimeListMax() const
{
   const simtime_p* motionTime = NULL;
   if(!motion_time_list.empty())
      motionTime = &(*motion_time_list.max());
   return motionTime;
}

const neighborhood_p*
Table::getOneHopNeighborhoodListMin() const
{
   const neighborhood_p* oneHopNeighborhood = NULL;
   if(!one_hop_neighborhood_list.empty())
      oneHopNeighborhood = 
      &(*one_hop_neighborhood_list.begin());
   return  oneHopNeighborhood; 
}

const neighborhood_p*
Table::getOneHopNeighborhoodListMax() const
{
   const neighborhood_p* oneHopNeighborhood = NULL;
   if(!one_hop_neighborhood_list.empty())
      oneHopNeighborhood =
      &(*one_hop_neighborhood_list.max());
   return  oneHopNeighborhood; 
}

const neighborhood_p*
Table::getKHopNeighborhoodListMin() const
{
   const neighborhood_p* kHopNeighborhood = NULL;
   if(!k_hop_neighborhood_list.empty())
      kHopNeighborhood =
      &(*k_hop_neighborhood_list.begin());
   return  kHopNeighborhood; 
}

const neighborhood_p*
Table::getKHopNeighborhoodListMax() const
{
   const neighborhood_p* kHopNeighborhood = NULL;
   if(!k_hop_neighborhood_list.empty())
      kHopNeighborhood =
      &(*k_hop_neighborhood_list.max());
   return  kHopNeighborhood; 
}

const role_p*
Table::getRoleListMin() const
{
   const role_p* role = NULL;
   if(!role_list.empty())
      role = &(*role_list.begin());
   return role;
}

const role_p*
Table::getRoleListMax() const
{
   const role_p* role = NULL;
   if(!role_list.empty())
      role = &(*role_list.max());
   return role;
}

const uint32_p*
Table::getCidListMin() const
{
   const uint32_p* cid = NULL;
   if(!cid_list.empty())
      cid = &(*cid_list.begin());
   return cid;
}

const uint32_p*
Table::getCidListMax() const
{
   const uint32_p* cid = NULL;
   if(!cid_list.empty())
      cid = &(*cid_list.max());
   return cid;
}

const coordp_bag*
Table::accessPositionList() const
{
   const coordp_bag* positionList = NULL;
   if(!position_list.empty())
      positionList = &position_list;
   return positionList;

}

const doublep_bag*
Table::accessDistanceList() const
{
   const doublep_bag* distanceList = NULL;
   if(!distance_list.empty())
      distanceList = &distance_list;
   return distanceList;
}

const doublep_bag*
Table::accessSpeedList() const
{
   const doublep_bag* speedList = NULL;
   if(!speed_list.empty())
      speedList = &speed_list;
   return speedList;
}

const doublep_bag*
Table::accessFlightLengthList() const
{
   const doublep_bag* flightLengthList = NULL;
   if(!flight_length_list.empty())
      flightLengthList = &flight_length_list;
   return flightLengthList;
}

const simtimep_bag*
Table::accessPauseTimeList() const
{
   const simtimep_bag* pauseTimeList = NULL;
   if(!pause_time_list.empty())
      pauseTimeList = &pause_time_list;
   return pauseTimeList;
}

const simtimep_bag*
Table::accessMotionTimeList() const
{
   const simtimep_bag* motionTimeList = NULL;
   if(!motion_time_list.empty())
      motionTimeList = &motion_time_list;
   return motionTimeList;
}

const neighborhoodp_bag*
Table::accessOneHopNeighborhoodList() const
{
   const neighborhoodp_bag* oneHopNeighborhoodList = NULL;
   if(!one_hop_neighborhood_list.empty())
      oneHopNeighborhoodList = &one_hop_neighborhood_list;
   return oneHopNeighborhoodList;
}


const neighborhoodp_bag*
Table::accessKHopNeighborhoodList() const
{
   const neighborhoodp_bag* kHopNeighborhoodList = NULL;
   if(!k_hop_neighborhood_list.empty())
      kHopNeighborhoodList = &k_hop_neighborhood_list;
   return kHopNeighborhoodList;
}

const rolep_bag*
Table::accessRoleList() const
{
   const rolep_bag* roleList = NULL;
   if(!role_list.empty())
      roleList = &role_list;
   return roleList;
}

const uint32p_bag*
Table::accessCidList() const
{
   const uint32p_bag* cidList = NULL;
   if(!cid_list.empty())
      cidList = &cid_list;
   return cidList;
}

unsigned int
Table::size() const
{
   return table.size();
}

void
Table::erase(uint32_t id)
{
   //If node exists in table then
   if(table.find(id) != table.end())
   {
      if(table[id].getPositionIterator().first)
         position_list.
         erase(table[id].getPositionIterator().second);
      if(table[id].getDistanceIterator().first)
         distance_list.
         erase(table[id].getDistanceIterator().second);      
      if(table[id].getSpeedIterator().first)
         speed_list.
         erase(table[id].getSpeedIterator().second);
      if(table[id].getFlightLengthIterator().first)
         flight_length_list.
         erase(table[id].getFlightLengthIterator().second);
      if(table[id].getPauseTimeIterator().first)
         pause_time_list.
         erase(table[id].getPauseTimeIterator().second);
      if(table[id].getMotionTimeIterator().first)
         motion_time_list.
         erase(table[id].getMotionTimeIterator().second);
      if(table[id].getOneHopIterator().first)
         one_hop_neighborhood_list.
         erase(table[id].getOneHopIterator().second);
      if(table[id].getKHopIterator().first)
         k_hop_neighborhood_list.
         erase(table[id].getKHopIterator().second);
      if(table[id].getRoleIterator().first)
         role_list.
         erase(table[id].getRoleIterator().second);
      if(table[id].getCidIterator().first)
         cid_list.
         erase(table[id].getCidIterator().second);
   }
   table.erase(id);
}

void
Table::clear()
{
   position_list.clear();
   distance_list.clear();
   speed_list.clear();
   flight_length_list.clear();
   pause_time_list.clear();
   motion_time_list.clear();
   one_hop_neighborhood_list.clear();
   k_hop_neighborhood_list.clear();
   role_list.clear();
   cid_list.clear();
   table.clear();
}

Table::iterator
Table::begin()
{
   auto it = table.begin();
   return it;
}

Table::iterator
Table::end()
{
   auto it = table.end();
   return it;
}

std::string
Table::info()
{
   std::string buffer;
   for(auto& pair : table)
   {
      buffer+=pair.second.info();
      buffer+="\n";
   }
   return buffer;
}

std::string
Table::info(uint32_t  id)
{
   std::string temp;
   if(table.find(id) != table.end())
      temp = table[id].info();
   return temp;
}
