#include "doublep_bag.h"

doublep_bag::doublep_bag(){}

doublep_bag::~doublep_bag(){}

doublep_bag::iterator
doublep_bag::insert(double_p pair_t)
{
   return bag.insert(pair_t);
}

doublep_bag::iterator
doublep_bag::insert(uint32_t id, double speed)
{
   double_p pair_t;
   pair_t.set(id,speed);
   return bag.insert(pair_t);
}

doublep_bag::iterator
doublep_bag::erase(iterator it)
{
   return bag.erase(it);
}

doublep_bag::iterator
doublep_bag::begin() const
{
   return bag.begin();
}

doublep_bag::iterator
doublep_bag::max() const
{
   return --bag.end();
}

doublep_bag::iterator
doublep_bag::end() const
{
   return bag.end();
}

unsigned int
doublep_bag::size()
{
   return bag.size();
}

unsigned int
doublep_bag::count(double_p pair_t)
{
   return bag.count(pair_t);
}

void
doublep_bag::clear()
{
   bag.clear();
}

bool
doublep_bag::empty()
{
   return bag.empty();
}

std::ostream&
operator << (std::ostream& os, doublep_bag& bag)
{
   doublep_bag::iterator it;
   std::string buffer;
   for(it = bag.begin();
       it != bag.end();
       it++)
   {
      buffer += std::to_string(it->key());
      buffer += ", ";
      buffer += std::to_string(it->value());
      buffer += "\n";
   }
   return os << buffer;
}
