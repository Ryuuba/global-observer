#include "uint8p_bag.h"

uint8p_bag::uint8p_bag(){}

uint8p_bag::~uint8p_bag(){}

uint8p_bag::iterator
uint8p_bag::insert(uint8_p pair_t)
{
   return bag.insert(pair_t);
}

uint8p_bag::iterator
uint8p_bag::insert(uint32_t id, uint8_t v)
{
   uint8_p temp;
   temp.set(id,v);
   return bag.insert(temp);
}

uint8p_bag::iterator
uint8p_bag::erase(iterator it)
{
   return bag.erase(it);
}

uint8p_bag::iterator
uint8p_bag::begin() const
{
   return bag.begin();
}

uint8p_bag::iterator
uint8p_bag::max() const
{
   return --bag.end();
}

uint8p_bag::iterator
uint8p_bag::end() const
{
   return bag.end();
}

unsigned int
uint8p_bag::size() const
{
   return bag.size();
}

unsigned int
uint8p_bag::count(uint8_p pair_t)
{
   return bag.count(pair_t);
}

void
uint8p_bag::clear()
{
   bag.clear();
}

bool
uint8p_bag::empty() const
{
   return bag.empty();
}

std::ostream&
operator << (std::ostream& os, uint8p_bag& bag)
{
   uint8p_bag::iterator it;
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
