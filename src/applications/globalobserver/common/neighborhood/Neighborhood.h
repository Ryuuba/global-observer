#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H
#include <iostream>
#include <set>
#include <utility>
#include <cstdint>
#include <string>

class Neighborhood
{
   public:
      //pair of kind <neighbor ID, hops>
      typedef std::pair<uint32_t,uint8_t> Neighbor;
      typedef std::set<Neighbor>::iterator iterator;
      typedef std::set<Neighbor>::
              const_iterator const_iterator;
      Neighborhood();
      virtual ~Neighborhood();
      virtual iterator insert(uint32_t id, uint8_t hops);
      virtual iterator insert(Neighbor neighbor);
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
      virtual void operator += (const Neighborhood& n);
      virtual bool operator ==
              (const Neighborhood& n) const;
      virtual bool operator !=
              (const Neighborhood& n) const;
   protected:
      std::set<Neighbor> neighborhood;
};

inline std::ostream&
operator << (std::ostream& os, Neighborhood& n)
{
   std::string buffer;
   for (auto& neighbor : n)
   {
      buffer+="neighbor ID: "
      buffer+=std::to_string((int)neighbor.first);
      buffer+=' ';
      buffer+="hops: ";
      buffer+=std::to_string((int)neighbor.second);
      buffer+= " ";
   }
   return os << buffer;
}

#endif
