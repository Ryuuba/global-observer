#include "Neighborhood.h"

Neighborhood::Neighborhood(){}

Neighborhood::~Neighborhood(){}

Neighborhood::iterator
Neighborhood::insert(uint32_t id, uint8_t hops)
{
   auto pair = std::make_pair(id,hops);
   return neighborhood.insert(pair).first;
}

Neighborhood::iterator
Neighborhood::insert(Neighborhood::Neighbor neighbor)
{
   return neighborhood.insert(neighbor).first;
}


unsigned int
Neighborhood::erase(uint32_t id)
{
   auto pair = std::make_pair(id,0);
   return neighborhood.erase(pair);
}

Neighborhood::iterator
Neighborhood::begin()
{
   return neighborhood.begin();
}

Neighborhood::iterator
Neighborhood::begin() const
{
   return neighborhood.begin();
}

Neighborhood::iterator
Neighborhood::end()
{
   return neighborhood.end();
}

Neighborhood::iterator
Neighborhood::end() const
{
   return neighborhood.end();
}

unsigned int
Neighborhood::size()
{
   return neighborhood.size();
}

unsigned int
Neighborhood::size() const
{
   return neighborhood.size();
}

void
Neighborhood::clear()
{
   neighborhood.clear();
}

Neighborhood::iterator
Neighborhood::find(uint32_t id)
{
   auto pair = std::make_pair(id,0);
   return neighborhood.find(pair);
}

Neighborhood::iterator
Neighborhood::find(uint32_t id) const
{
   auto pair = std::make_pair(id,0);
   return neighborhood.find(pair);
}

std::string
Neighborhood::info() const
{
   std::string buffer;
   if(!neighborhood.empty())
      for (auto& neighbor : neighborhood)
      {
         buffer+="neighbor ID: "
         buffer+=std::to_string((int)neighbor.first);
         buffer+=' ';
         buffer+="hops: ";
         buffer+=std::to_string((int)neighbor.second);
         buffer+= " ";
      }
   return buffer;
}

Neighborhood
neighborhood::operator + (const Neighborhood& n) const
{
   Neighborhood temp;
   temp = *this;
   for(auto& neighbor : n)
      temp.insert(neighbor);
   return temp;
}

void
Neighborhood::operator += (const neighborhood& n)
{
   for(auto& neighbor : n)
      this->insert(neighbor);
}

bool
Neighborhood::operator == (const neighborhood& n) const
{
   return *this == n;
}

bool
Neighborhood::operator != (const neighborhood& n) const
{
   return !(*this == n);
}
