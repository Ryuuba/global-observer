#include "coordp_bag.h"

coordp_bag::coordp_bag(){}

coordp_bag::~coordp_bag(){}

coordp_bag::iterator
coordp_bag::insert(coord_p pair_t)
{
   return bag.insert(pair_t);
}

coordp_bag::iterator
coordp_bag::insert(uint32_t id, Coord position)
{
   coord_p pair_t;
   pair_t.set(id,position);
   return bag.insert(pair_t);
}

coordp_bag::iterator
coordp_bag::erase(iterator it)
{
   return bag.erase(it);
}

coordp_bag::iterator
coordp_bag::begin()
{
   return bag.begin();
}

coordp_bag::iterator
coordp_bag::max()
{
   return --bag.end();
}

coordp_bag::iterator
coordp_bag::end()
{
   return bag.end();
}

unsigned int
coordp_bag::size()
{
   return bag.size();
}

unsigned int
coordp_bag::count(coord_p pair_t)
{
   return bag.count(pair_t);
}

void
coordp_bag::clear()
{
   bag.clear();
}

std::ostream&
operator << (std::ostream& os, coordp_bag& bag)
{
   coordp_bag::iterator it;
   std::string buffer;
   for(it = bag.begin();
       it != bag.end();
       it++)
   {
      buffer += std::to_string(it->key());
      buffer += ", (";
      buffer += std::to_string(it->value().x);
      buffer += ", ";
      buffer += std::to_string(it->value().y);
      buffer += ')';
      buffer += "\n";
   }
   return os << buffer;
}
