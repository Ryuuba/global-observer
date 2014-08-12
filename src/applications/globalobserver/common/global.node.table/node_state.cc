#include "node_state.h"

node_state::node_state()
{
    isUidSet = false;
    isCidSet = false;
    isPositionSet = false;
    isPauseTimeSet = false;
    isMotionTimeSet = false;
    isSpeedSet = false;
    isFlightLengthSet = false;
    isOneHopSet = false;
    isKHopSet = false;
    isRoleSet = false;
}

node_state::~node_state(){}

//It returns a pointer to the ID of a node. In case of the
//ID has not already been set, the method returns a NULL
//pointer
const uint32_t*
node_state::getUID() const
{
   if(isUidSet)
      return (const uint32_t*) &UID;
   else
      return NULL;
}

//It sets the ID of a node and turns on the flag indicating
//the ID is valid
void
node_state::setUID(uint32_t id)
{
   UID = id;
   isUidSet = true;
}

//It returns a pointer to the position of a node. When the
//position iterator is invalid, the method returns
//a NULL pointer
const Coord*
node_state::getPosition() const
{
   const Coord* temp_position = NULL;
   if(isPositionSet)
      temp_position = position->value_p();
   return temp_position;
}

//It returns, into a pair structure, a bool value and an
//iterator pointing to the position of a node. The bool
//value informs if the iterator is valid
std::pair<bool,coordp_bag::iterator>
node_state::getPositionIterator()
{
   return std::make_pair(isPositionSet,position);
}

//It sets the position iterator and turn on the flag
//indicating the position iterator of a node is valid
void node_state::setPosition(coordp_bag::iterator it)
{
   position = it;
   isPositionSet = true;
}

//It returns a pointer to the speed of a node. When the
//speed iterator is invalid, the method returns
//a NULL pointer
const double*
node_state::getSpeed() const
{
   const double* temp_speed = NULL;
   if(isSpeedSet)
      temp_speed = speed->value_p();
   return temp_speed;
}

//It returns, into a pair structure, a bool value and an
//iterator pointing to the speed of a node. The bool informs
//if the speed iterator is valid.
std::pair<bool,doublep_bag::iterator>
node_state::getSpeedIterator()
{
   return make_pair(isSpeedSet,speed);
}

//It sets the speed of a node. Besides, it turns on the flag
//indicating the speed iterator is valid
void node_state::setSpeed(doublep_bag::iterator it)
{
   speed = it;
   isSpeedSet = true;
}

//It returns a pointer to the flight-length of a node. When
//the flight-length iterator is invalid, the method returns
//a NULL pointer.
const double*
node_state::getFlightLength() const
{
   const double* temp_flight_length = NULL;
   if(isFlightLengthSet)
      temp_flight_length = flight_length->value_p();
   return temp_flight_length;
}

//It returns, into a pair structure, a bool value and an
//iterator pointing to the flight-length of a node. The bool
//value informs if the flight-length iterator is valid.
std::pair<bool,doublep_bag::iterator>
node_state::getFlightLengthIterator()
{
   return std::make_pair(isFlightLengthSet,flight_length);
}

//It sets the flight-length iterator of a node. Besides,
//it turns on the flag indicating the flight-length iterator
//is valid
void
node_state::setFlightLength(doublep_bag::iterator it)
{
   flight_length = it;
   isFlightLengthSet = true;
}

//It returns a pointer to the pause-time of a node. When the
//pause-time iterator is invalid, the method
//returns a NULL pointer
const simtime_t*
node_state::getPauseTime() const
{
   const simtime_t* temp_pause_time = NULL;
   if(isPauseTimeSet)
      temp_pause_time = pause_time->value_p();
   return temp_pause_time;
}

//It returns, into a pair structure, a bool value and an
//iterator pointing to the pause-time of a node. The bool
//value informs if the pause-time iterator is valid.
std::pair<bool,simtimep_bag::iterator>
node_state::getPauseTimeIterator()
{
   return std::make_pair(isPauseTimeSet, pause_time);
}

//It sets the pause-time iterator of a node. Besides,
//it turns on the flag indicating the pause time is set
void
node_state::setPauseTime(simtimep_bag::iterator it)
{
   pause_time = it;
   isPauseTimeSet = true;
}

//It returns a pointer to the motion-time of a node. When
//the pause-time iterator is invalid, the method returns a
//NULL pointer.
const simtime_t*
node_state::getMotionTime() const
{
   const simtime_t* temp_motion_time = NULL;
   if(isMotionTimeSet)
      temp_motion_time = motion_time->value_p();
   return temp_motion_time;
}

//It returns, into a pair structure, a bool value and an
//iterator pointing to the motion-time of a node. The bool
//value informs if the motion-time iterator is valid.
std::pair<bool,simtimep_bag::iterator>
node_state::getMotionTimeIterator()
{
   return std::make_pair(isMotionTimeSet,motion_time);
}

//It sets the motion time iterator of a node. Besides,
//it turns on the flag indicating the motion-time iterator
//is set
void
node_state::setMotionTime(simtimep_bag::iterator it)
{
   motion_time = it;
   isMotionTimeSet = true;
}

//It returns a pointer to the neighborhood of a node. When
//the neighborhood iterator is invalid, the method returns a
//NULL pointer
const Neighborhood*
node_state::getOneHop() const
{
   const Neighborhood* temp_neighborhood = NULL;
   if(isOneHopSet)
      temp_neighborhood = one_hop->value_p();
   return temp_neighborhood;
}

/*
//It returns a pointer to the size of the
//one-hop-neighborhood of a node. If the corresponding
//iterator is not set, then a NULL pointer is returned.
unsigned int*
node_state::getDegree()
{
   int* temp_degree = NULL;
   if(isOneHopSet)
      temp_degree = new int(one_hop->value().size());
   return temp_degree;
}
*/

//It returns, into a pair structure, a bool value and an
//iterator pointing to the one-hop neighborhoof of a node.
//The bool value informs if the neighborhood iterator
//is valid.
std::pair<bool,neighborhoodp_bag::iterator>
node_state::getOneHopIterator()
{
   return std::make_pair(isOneHopSet, one_hop);
}

//It sets the one-hop-neighborhood iterator of a node.
//Besides, it turns on the flag indicating the iterator
//is valid
void
node_state::setOneHop(neighborhoodp_bag::iterator it)
{
   one_hop = it;
   isOneHopSet = true;
}

//It returns a pointer to the k-hop neighborhood of a node.
//When the k-hop-neighborhood iterator is invalid,
//the method returns a NULL pointer
const Neighborhood*
node_state::getKHop() const
{
   const Neighborhood* temp_neighborhood = NULL;
   if(isKHopSet)
      temp_neighborhood = k_hop->value_p();
   return temp_neighborhood;
}

/*
//It returns a pointer to the size of the k-hop-neighborhood
//of a node. If the corresponding iterator is not set, then
//a NULL pointer is returned.
unsigned int*
node_state::getKHopSize()
{
   unsigned int* temp_k_hop_size = NULL;
   if(isKHopSet)
      temp_k_hop_size = new int(k_hop->value().size());
   return temp_k_hop_size;
}
*/

//It returns, into a pair structure, a bool value and an
//iterator pointing to the k-hop neighborhoof of a node.
//The bool value informs if the k-hop-neighborhood iterator
//is valid.
std::pair<bool,neighborhoodp_bag::iterator>
node_state::getKHopIterator()
{
   return std::make_pair(isKHopSet, k_hop);
}

//It sets the k-hop-neighborhood iterator of a node.
//Besides, it turns on the flag indicating the iterator
//is valid
void
node_state::setKHop(neighborhoodp_bag::iterator it)
{
   k_hop = it;
   isKHopSet = true;
}

//It returns a pointer to the role of a node. When the role
//iterator is invalid, the method returns a NULL pointer
const Role*
node_state::getRole() const
{
   const Role* temp_role = NULL;
   if(isRoleSet)
      temp_role = role->value_p();
   return temp_role;
}

//It returns, into a pair structure, a bool value and an
//iterator pointing to the role of a node. The bool value
//informs if the role iterator is valid.
std::pair<bool,rolep_bag::iterator>
node_state::getRoleIterator()
{
   return std::make_pair(isRoleSet,role);
}

//It sets the role iterator of a node. Besides, it turns on
//the flag indicating the iterator is valid
void
node_state::setRole(rolep_bag::iterator it)
{
   role = it;
   isRoleSet = true;
}

//It returns a pointer to the CID of a node. When the CID
//iterator is invalid, the method returns a NULL pointer
const uint32_t*
node_state::getCid() const
{
   const uint32_t* temp_cid = NULL;
   if(isCidSet)
      temp_cid = cid->value_p();
   return temp_cid;
}

//It returns, into a pair structure, a bool value and an
//iterator pointing to the CID of a node. The bool value
//informs if the CID iterator is valid.
std::pair<bool,uint32p_bag::iterator>
node_state::getCidIterator()
{
   return std::make_pair(isCidSet,cid);
}

//It sets the CID iterator of a node. Besides, it turns on
//the flag indicating the iterator is valid
void
node_state::setCid(uint32p_bag::iterator it)
{
   cid = it;
   isCidSet = true;
}

std::string
node_state::info()
{
   std::string buffer("\n");
   //concatenate the node ID if it exists
   if(isUidSet)
   {
      buffer += "Node ID: ";
      buffer += std::to_string((int)(*getUID()));
      buffer += '\n';
   }
   //concatenate the position units m
   if(isPositionSet)
   {
      buffer += "Position: ";
      buffer += " (";
      buffer += std::to_string(position->value().x);
      buffer+= ", ";
      buffer += std::to_string(position->value().y);
      buffer += ")\n";
   }
   //concatenate the pause-time units s
   if(isPauseTimeSet)
   {
      buffer += "Pause time: ";
      buffer += std::to_string(pause_time->value().dbl());
      buffer += '\n';
   }
   //concatenate the motion-time units s
   if(isMotionTimeSet)
   {
      buffer += "Motion time: ";
      buffer += std::to_string(motion_time->value().dbl());
      buffer += '\n';
   }
   //concatenate the speed units s
   if(isSpeedSet)
   {
      buffer += "Speed: ";
      buffer += std::to_string(speed->value());
      buffer += '\n';
   }
   //concatenate the flight length units m
   if(isFlightLengthSet)
   {
      buffer += "Flight length: ";
      buffer += std::to_string(flight_length->value());
      buffer += '\n';
   }
   //concatenate the neighborhood
   if(isOneHopSet)
   {
      buffer += "Neighborhood: ";
      buffer += one_hop->value().info();
      buffer += '\n';
   }
   //concatenate the k-hop neighborhood
   if(isKHopSet)
   {
      buffer += "K-hop neighborhood: ";
      buffer += k_hop->value().info();
      buffer += '\n';
   }
   if(isCidSet)
   {
      buffer += "CID: ";
      buffer += std::to_string((int)cid->value());
      buffer += '\n';
   }
   if(isRoleSet)
   {
      buffer += "Role: ";
      if(role->value() == Role::UNCLUSTERED)
         buffer += "UNCLUSTERED";
      else if(role->value() == Role::CLUSTERED)
         buffer += "CLUSTERED";
      else if(role->value() == Role::GATEWAY)
         buffer += "GATEWAY";
      else
         buffer += "LEADER";
      buffer += '\n';
   }
   return buffer;
}
