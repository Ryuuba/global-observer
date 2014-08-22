#include "rolep_bag.h"

rolep_bag::rolep_bag(){}

rolep_bag::~rolep_bag(){}

rolep_bag::iterator
rolep_bag::insert(role_p pair_t)
{
   return bag.insert(pair_t);
}

rolep_bag::iterator
rolep_bag::insert(uint32_t id, Role r)
{
   role_p temp;
   temp.set(id,r);
   return bag.insert(temp);
}

rolep_bag::iterator
rolep_bag::erase(iterator it)
{
   return bag.erase(it);
}

rolep_bag::iterator
rolep_bag::begin()
{
   return bag.begin();
}

rolep_bag::iterator
rolep_bag::begin() const
{
   return bag.begin();
}


rolep_bag::iterator
rolep_bag::max()
{
   return --bag.end();
}

rolep_bag::iterator
rolep_bag::max() const
{
   return --bag.end();
}


rolep_bag::iterator
rolep_bag::end()
{
   return bag.end();
}

rolep_bag::iterator
rolep_bag::end() const
{
   return bag.end();
}


unsigned int
rolep_bag::size()
{
   return bag.size();
}

unsigned int
rolep_bag::count(role_p pair_t)
{
   return bag.count(pair_t);
}

//bag elements are ordered according to their value: the
//second element in a role_p pair, it means this method
//returns the number of elements with certain role "r" in
//the bag

unsigned int
rolep_bag::count(Role r) const
{
   role_p role;
   role.set(0,r);
   return bag.count(role);
}

void
rolep_bag::clear()
{
   bag.clear();
}

bool
rolep_bag::empty() const
{
   return bag.empty();
}

//Search for nodes with role LEADER. Note that the key 0 is
//not used in the search.
std::pair<rolep_bag::iterator,rolep_bag::iterator>
rolep_bag::equalRange(Role r)
{
   role_p leader;
   leader.set(0,r);
   return bag.equal_range(leader);
}

std::pair<rolep_bag::iterator,rolep_bag::iterator>
rolep_bag::equalRange(Role r) const
{
   role_p leader;
   leader.set(0, r);
   return bag.equal_range(leader);
}


std::ostream&
operator << (std::ostream& os, rolep_bag& bag)
{
   rolep_bag::iterator it;
   std::string buffer, status;
   it = bag.begin();

   switch(it->value())
   {
      case Role::UNCLUSTERED:
         status = "UNCLUSTERED";
         break;
      case Role::CLUSTERED:
         status = "CLUSTERED";
         break;
      case Role::GATEWAY:
         status = "GATEWAY";
         break;
      default:
         status = "LEADER";
         break;
   }

   for(it = bag.begin();
       it != bag.end();
       it++)
   {
      buffer += std::to_string(it->key());
      buffer += ", ";
      buffer += status;
      buffer += "\n";
   }
   return os << buffer;
}
