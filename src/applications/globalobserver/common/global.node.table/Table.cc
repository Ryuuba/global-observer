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
         position_list.erase(table[id].getPositionIterator().second);
      if(table[id].getSpeedIterator().first)
         speed_list.erase(table[id].getSpeedIterator().second);
      if(table[id].getFlightLengthIterator().first)
         flight_length_list.erase(table[id].getFlightLengthIterator().second);
      if(table[id].getPauseTimeIterator().first)
         pause_time_list.erase(table[id].getPauseTimeIterator().second);
      if(table[id].getMotionTimeIterator().first)
         motion_time_list.erase(table[id].getMotionTimeIterator().second);
      if(table[id].getOneHopIterator().first)
         one_hop_neighborhood_list.erase(table[id].getOneHopIterator().second);
      if(table[id].getKHopIterator().first)
         k_hop_neighborhood_list.erase(table[id].getKHopIterator().second);
      if(table[id].getRoleIterator().first)
         role_list.erase(table[id].getRoleIterator().second);
      if(table[id].getCidIterator().first)
         cid_list.erase(table[id].getCidIterator().second);
   }
   table.erase(id);
}

void
Table::clear()
{
   position_list.clear();
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
