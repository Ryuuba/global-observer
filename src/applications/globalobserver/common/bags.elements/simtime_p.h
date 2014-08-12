#ifndef SIMTIME_P_H
#define SIMTIME_P_H
#include <iostream>
#include <cstdint>
#include <utility>
#include <omnetpp.h>

// par <key,value>. comparisons are performed considering
// the value
class simtime_p
{
   protected:
      std::pair<uint32_t,simtime_t> pair;
   public:
      simtime_p();
      virtual ~simtime_p();
      virtual void set(uint32_t key, simtime_t value);
      virtual uint32_t key() const;
      virtual const uint32_t* key_p() const;
      virtual void key(uint32_t k);
      virtual simtime_t value() const;
      virtual const simtime_t* value_p() const;
      virtual void value(simtime_t v);
      virtual bool operator < (const simtime_p& pair_t) const;
      virtual bool operator <= (const simtime_p& pair_t) const;
      virtual bool operator > (const simtime_p& pair_t) const;
      virtual bool operator >= (const simtime_p& pair_t) const;
      virtual bool operator == (const simtime_p& pair_t) const;
      virtual bool operator != (const simtime_p& pair_t) const;
};

inline std::ostream&
operator << (std::ostream& os, const simtime_p& pair_t)
{
   return os << pair_t.key() << ", " << pair_t.value().dbl();
}
#endif
