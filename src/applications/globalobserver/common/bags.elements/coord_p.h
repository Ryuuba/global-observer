#ifndef COORD_P_H
#define COORD_P_H
#include <iostream>
#include <cstdint>
#include <utility>
#include "Coord.h"

// par <key,value>. comparisons are performed considering
// the value
class coord_p
{
   protected:
      std::pair<uint32_t,Coord> pair;
   public:
      coord_p();
      virtual ~coord_p();
      virtual void set(uint32_t key, Coord value);
      virtual uint32_t key() const;
      virtual const uint32_t* key_p() const;
      virtual void key(uint32_t k);
      virtual Coord value() const;
      virtual const Coord* value_p() const;
      virtual void value(Coord v);
      virtual bool operator < (const coord_p& pair_t) const;
      virtual bool operator <= (const coord_p& pair_t) const;
      virtual bool operator > (const coord_p& pair_t) const;
      virtual bool operator >= (const coord_p& pair_t) const;
      virtual bool operator == (const coord_p& pair_t) const;
      virtual bool operator != (const coord_p& pair_t) const;
};

inline std::ostream&
operator << (std::ostream& os, coord_p& pair_t)
{
   return os << pair_t.key() << ", " << '('
             << pair_t.value().x << ", "
             << pair_t.value().y << ')';
}
#endif
