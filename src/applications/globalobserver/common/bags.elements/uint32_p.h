#ifndef _UINT32_P_H
#define _UINT32_P_H
#include <iostream>
#include <cstdint>
#include <utility>

// par <key,value>. comparisons are performed considering
// the value
class uint32_p
{
   protected:
      std::pair<uint32_t,uint32_t> pair;
   public:
      uint32_p();
      virtual ~uint32_p();
      virtual void set(uint32_t key, uint32_t value);
      virtual uint32_t key() const;
      virtual const uint32_t* key_p() const;
      virtual void key(uint32_t k);
      virtual uint32_t value() const;
      virtual const uint32_t* value_p() const;
      virtual void value(uint32_t v);
      virtual bool operator < (const uint32_p& pair_t) const;
      virtual bool operator <= (const uint32_p& pair_t) const;
      virtual bool operator > (const uint32_p& pair_t) const;
      virtual bool operator >= (const uint32_p& pair_t) const;
      virtual bool operator == (const uint32_p& pair_t) const;
      virtual bool operator != (const uint32_p& pair_t) const;
};

inline std::ostream&
operator << (std::ostream& os, const uint32_p& pair_t)
{
   return os << pair_t.key() << ", " << pair_t.value();
}
#endif
