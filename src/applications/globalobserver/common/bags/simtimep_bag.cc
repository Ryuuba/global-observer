#include "simtimep_bag.h"

simtimep_bag::simtimep_bag(){}

simtimep_bag::~simtimep_bag(){}

simtimep_bag::iterator
simtimep_bag::insert(simtime_p pair_t)
{
   return bag.insert(pair_t);
}


simtimep_bag::iterator
simtimep_bag::insert(uint32_t id, simtime_t time)
{
   simtime_p pair_t;
   pair_t.set(id,time);
   return bag.insert(pair_t);
}

simtimep_bag::iterator
simtimep_bag::erase(iterator it)
{
   return bag.erase(it);
}

simtimep_bag::iterator
simtimep_bag::begin() const
{
   return bag.begin();
}

simtimep_bag::iterator
simtimep_bag::max() const
{
   return --bag.end();
}

simtimep_bag::iterator
simtimep_bag::end() const
{
   return bag.end();
}

unsigned int
simtimep_bag::size()
{
   return bag.size();
}

unsigned int
simtimep_bag::count(simtime_p pair_t)
{
   return bag.count(pair_t);
}

void
simtimep_bag::clear()
{
   bag.clear();
}

bool
simtimep_bag::empty() const
{
   return bag.empty();
}

std::ostream&
operator << (std::ostream& os, simtimep_bag& bag)
{
   simtimep_bag::iterator it;
   std::string buffer;
   for(it = bag.begin();
       it != bag.end();
       it++)
   {
      buffer += std::to_string(it->key());
      buffer += ", ";
      buffer += std::to_string(it->value().dbl());
      buffer += "\n";
   }
   return os << buffer;
}
