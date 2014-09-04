#include "Neighborhood.h"

Neighborhood::Neighborhood(){}

Neighborhood::~Neighborhood(){}

void
Neighborhood::insert(uint32_t id, uint8_t hops)
{
   neighborhood[id] = hops;
}

void
Neighborhood::insert(Neighborhood::Neighbor neighbor)
{
   neighborhood[neighbor.first] = neighbor.second;
}

uint8_t
Neighborhood::value(uint32_t id)
{
   uint8_t result = 255;
   if(neighborhood.find(id) != neighborhood.end())
      result = neighborhood.find(id)->second;
   return result;

}

uint8_t
Neighborhood::value(uint32_t id) const
{
   uint8_t result = 255;
   if(neighborhood.find(id) != neighborhood.end())
      result = neighborhood.find(id)->second;
   return result;
}


unsigned int
Neighborhood::erase(uint32_t id)
{
   return neighborhood.erase(id);
}

Neighborhood::iterator
Neighborhood::begin()
{
   return neighborhood.begin();
}

Neighborhood::const_iterator
Neighborhood::begin() const
{
   return neighborhood.begin();
}

Neighborhood::iterator
Neighborhood::end()
{
   return neighborhood.end();
}

Neighborhood::const_iterator
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

bool
Neighborhood::empty()
{
   return neighborhood.empty();
}

bool
Neighborhood::empty() const
{
   return neighborhood.empty();
}


void
Neighborhood::clear()
{
   neighborhood.clear();
}

Neighborhood::iterator
Neighborhood::find(uint32_t id)
{
   return neighborhood.find(id);
}

Neighborhood::const_iterator
Neighborhood::find(uint32_t id) const
{
   return neighborhood.find(id);
}

std::string
Neighborhood::info() const
{
   std::string buffer;
   if(!neighborhood.empty())
      for (auto& neighbor : neighborhood)
      {
         buffer+='<';
         buffer+=std::to_string((int)neighbor.first);
         buffer+=", ";
         buffer+=std::to_string((int)neighbor.second);
         buffer+= '>';
      }
   return buffer;
}

Neighborhood
Neighborhood::operator + (const Neighborhood& n) const
{
   Neighborhood temp;
   temp = *this;
   for(auto& neighbor : n)
      temp.insert(neighbor);
   return temp;
}

void
Neighborhood::operator += (const Neighborhood& n)
{
   for(auto& neighbor : n)
      this->insert(neighbor);
}

bool
Neighborhood::operator == (const Neighborhood& n) const
{
   return *this == n;
}

bool
Neighborhood::operator != (const Neighborhood& n) const
{
   return !(*this == n);
}
