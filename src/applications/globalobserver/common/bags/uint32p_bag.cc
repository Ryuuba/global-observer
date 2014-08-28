#include "uint32p_bag.h"

uint32p_bag::uint32p_bag(){}

uint32p_bag::~uint32p_bag(){}

uint32p_bag::iterator
uint32p_bag::insert(uint32_p pair_t)
{
   return bag.insert(pair_t);
}

uint32p_bag::iterator
uint32p_bag::insert(uint32_t id, uint32_t v)
{
   uint32_p temp;
   temp.set(id,v);
   return bag.insert(temp);
}

uint32p_bag::iterator
uint32p_bag::erase(iterator it)
{
   return bag.erase(it);
}

uint32p_bag::iterator
uint32p_bag::begin() const
{
   return bag.begin();
}

uint32p_bag::iterator
uint32p_bag::max() const
{
   return --bag.end();
}

uint32p_bag::iterator
uint32p_bag::end() const
{
   return bag.end();
}

unsigned int
uint32p_bag::size()
{
   return bag.size();
}

unsigned int
uint32p_bag::count(uint32_p pair_t)
{
   return bag.count(pair_t);
}

void
uint32p_bag::clear()
{
   bag.clear();
}

bool
uint32p_bag::empty() const
{
   return bag.empty();
}

std::pair<uint32p_bag::iterator,uint32p_bag::iterator>
uint32p_bag::equalRange(uint32_t v) const
{
   uint32_p pair;
   pair.set(0,v);
   return bag.equal_range(pair);
}


std::ostream&
operator << (std::ostream& os, uint32p_bag& bag)
{
   uint32p_bag::iterator it;
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
