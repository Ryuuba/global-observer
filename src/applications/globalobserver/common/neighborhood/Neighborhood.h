#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <cstdint>
#include <string>

class Neighborhood
{
   public:
      //pair of kind <neighbor ID, hops>
      typedef std::pair<uint32_t,uint8_t> Neighbor;
      typedef std::unordered_map<uint32_t, uint8_t>::
              iterator iterator;
      typedef std::unordered_map<uint32_t, uint8_t>::
              const_iterator const_iterator;
      Neighborhood();
      virtual ~Neighborhood();
      virtual void insert(uint32_t id, uint8_t hops);
      virtual void insert(Neighbor neighbor);
      virtual uint8_t value(uint32_t id);
      virtual uint8_t value(uint32_t id) const;
      virtual unsigned int erase(uint32_t id);
      virtual iterator begin();
      virtual iterator end();
      virtual const_iterator begin() const;
      virtual const_iterator end() const;
      virtual unsigned int size();
      virtual unsigned int size() const;
      virtual bool empty();
      virtual bool empty() const;
      virtual void clear();
      virtual iterator find(uint32_t id);
      virtual const_iterator find(uint32_t id) const;
      virtual std::string info() const;
      virtual Neighborhood operator+
              (const Neighborhood& n) const;
      virtual void operator += (const Neighborhood& n);
      virtual bool operator ==
              (const Neighborhood& n) const;
      virtual bool operator !=
              (const Neighborhood& n) const;
   protected:
      std::unordered_map<uint32_t, uint8_t> neighborhood;
};

inline std::ostream&
operator << (std::ostream& os, Neighborhood& n)
{
   std::string buffer;
   for (auto& neighbor : n)
   {
      buffer+="neighbor ID: ";
      buffer+=std::to_string((int)neighbor.first);
      buffer+=' ';
      buffer+="hops: ";
      buffer+=std::to_string((int)neighbor.second);
      buffer+= " ";
   }
   return os << buffer;
}

#endif
