#include "Neighborhood.h"

Neighborhood::Neighborhood(){}

Neighborhood::~Neighborhood(){}

Neighborhood::iterator
Neighborhood::insert(uint32_t id)
{
   return vicinity.insert(id).first;
}

unsigned int
Neighborhood::erase(uint32_t id)
{
   return vicinity.erase(id);
}

Neighborhood::iterator
Neighborhood::begin()
{
   return vicinity.begin();
}

Neighborhood::iterator
Neighborhood::begin() const
{
   return vicinity.begin();
}

Neighborhood::iterator
Neighborhood::end()
{
   return vicinity.end();
}

Neighborhood::iterator
Neighborhood::end() const
{
   return vicinity.end();
}

unsigned int
Neighborhood::size()
{
   return vicinity.size();
}

unsigned int
Neighborhood::size() const
{
   return vicinity.size();
}

void
Neighborhood::clear()
{
   vicinity.clear();
}

Neighborhood::iterator
Neighborhood::find(uint32_t id)
{ 
   return vicinity.find(id);
}

Neighborhood::iterator
Neighborhood::find(uint32_t id) const
{ 
   return vicinity.find(id);
}

Neighborhood
Neighborhood::operator + (const Neighborhood& n) const
{
   Neighborhood temp;
   Neighborhood::iterator it;
   temp = *this;
   for (it = n.begin(); it != n.end(); it++)
      temp.insert(*it);
   return temp;
}

void
Neighborhood::operator += (const Neighborhood& n)
{
   Neighborhood::iterator it;
   for (it = n.begin(); it != n.end(); it++)
      this->insert(*it);
}

bool
Neighborhood::operator == (const Neighborhood& n) const
{
   return (vicinity == n.vicinity);
}

bool
Neighborhood::operator != (const Neighborhood& n) const
{
   return !(vicinity == n.vicinity);
}

std::string
Neighborhood::info() const
{
   std::string buffer;
   if(!vicinity.empty())
   for (auto& neighbor : vicinity)
      {
         buffer+=std::to_string((int)neighbor);
         buffer+= " ";
      }
   return buffer;
}
