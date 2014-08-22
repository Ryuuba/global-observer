#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H
#include <iostream>
#include <set>
#include <cstdint>
#include <string>

class Neighborhood
{
   protected:
      std::set<uint32_t> vicinity;
   public:
      typedef std::set<uint32_t>::iterator iterator;
      typedef std::set<uint32_t>::const_iterator const_iterator;
      Neighborhood();
      virtual ~Neighborhood();
      virtual iterator insert(uint32_t id);
      virtual unsigned int erase(uint32_t id);
      virtual iterator begin();
      virtual iterator end();
      virtual iterator begin() const;
      virtual iterator end() const;
      virtual unsigned int size();
      virtual unsigned int size() const;
      virtual void clear();
      virtual iterator find(uint32_t id);
      virtual iterator find(uint32_t id) const;
      virtual Neighborhood operator+
      (const Neighborhood& n) const;
      virtual void operator+= (const Neighborhood& n);
      virtual bool operator==
      (const Neighborhood& n) const;
      virtual bool operator!=
      (const Neighborhood& n) const;
      virtual std::string info() const;
};

inline std::ostream&
operator << (std::ostream& os, Neighborhood& n)
{
   std::string buffer;
   Neighborhood::iterator it;

   for (it = n.begin(); it != n.end(); it++)
   {
      buffer+=std::to_string((int)*it);
      buffer+= " ";
   }
   return os << buffer;
}

#endif
