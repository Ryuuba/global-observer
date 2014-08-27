#ifndef UINT32_P_H
#define UINT32_P_H
#include <iostream>
#include <cstdint>
#include <utility>
#include "Neighborhood.h"

// par <key,value>. comparisons are performed considering
// the value, which is a node set
class neighborhood_p
{
   protected:
      std::pair<uint32_t,Neighborhood> pair;
   public:
      neighborhood_p();
      virtual ~neighborhood_p();
      virtual void set(uint32_t key, Neighborhood& value);
      virtual uint32_t key() const;
      virtual const uint32_t* key_p() const;
      virtual void key(uint32_t k);
      virtual Neighborhood value() const;
      virtual const Neighborhood* value_p() const;
      virtual void value(Neighborhood n);
      virtual void insert(Neighborhood::Neighbor neighbor);
      virtual bool
      operator == (const neighborhood_p& pair_t) const;
      virtual bool
      operator != (const neighborhood_p& pair_t) const;
      virtual bool
      operator < (const neighborhood_p& pair_t) const;
      virtual bool
      operator <= (const neighborhood_p& pair_t) const;
      virtual bool
      operator > (const neighborhood_p& pair_t) const;
      virtual bool
      operator >= (const neighborhood_p& pair_t) const;
};

inline std::ostream&
operator << (std::ostream& o, const neighborhood_p& pair_t)
{
   return o << pair_t.key() << ": "
             << pair_t.value().info();
}
#endif
