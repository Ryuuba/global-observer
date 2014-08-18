#include "neighborhoodp_bag.h"

neighborhoodp_bag::neighborhoodp_bag(){}

neighborhoodp_bag::~neighborhoodp_bag(){}

neighborhoodp_bag::iterator
neighborhoodp_bag::insert(neighborhood_p pair_t)
{
   return bag.insert(pair_t);
}

neighborhoodp_bag::iterator
neighborhoodp_bag::insert(uint32_t id, Neighborhood n)
{
   neighborhood_p temp;
   temp.set(id,n);
   return bag.insert(temp);
}

neighborhoodp_bag::iterator
neighborhoodp_bag::erase(neighborhoodp_bag::iterator it)
{
   return bag.erase(it);
}

neighborhoodp_bag::iterator
neighborhoodp_bag::begin()
{
   return bag.begin();
}

neighborhoodp_bag::iterator
neighborhoodp_bag::begin() const
{
   return bag.begin();
}

neighborhoodp_bag::iterator
neighborhoodp_bag::end()
{
   return bag.end();
}

neighborhoodp_bag::iterator
neighborhoodp_bag::end() const
{
   return bag.end();
}

neighborhoodp_bag::iterator
neighborhoodp_bag::max()
{
   return --bag.end();
}
unsigned int
neighborhoodp_bag::size()
{
   return bag.size();
}

void
neighborhoodp_bag::clear()
{
   bag.clear();
}

bool
neighborhoodp_bag::empty()
{
   return bag.empty();
}

std::ostream&
operator <<(std::ostream& os, const neighborhoodp_bag& bag)
{
   neighborhoodp_bag::iterator it;
   std::string buffer;
   for(it = bag.begin(); it != bag.end(); it++)
   {
      buffer += it->value().info();
      buffer += " ";
   }
   return os << buffer;
}

