#ifndef UINT8_P_H
#define UINT8_P_H
#include <iostream>
#include <cstdint>
#include <utility>

// par <key,value>. comparisons are performed considering
// the value
class uint8_p
{
   protected:
      std::pair<uint32_t,uint8_t> pair;
   public:
      uint8_p();
      virtual ~uint8_p();
      virtual void set(uint32_t key, uint8_t value);
      virtual uint32_t key() const;
      virtual const uint32_t* key_p() const;
      virtual void key(uint32_t k);
      virtual uint8_t value() const;
      virtual const uint8_t* value_p() const;
      virtual void value(uint8_t v);
      virtual bool operator < (const uint8_p& pair_t) const;
      virtual bool operator <= (const uint8_p& pair_t) const;
      virtual bool operator > (const uint8_p& pair_t) const;
      virtual bool operator >= (const uint8_p& pair_t) const;
      virtual bool operator == (const uint8_p& pair_t) const;
      virtual bool operator != (const uint8_p& pair_t) const;
};

inline std::ostream&
operator << (std::ostream& os, const uint8_p& pair_t)
{
   return os << pair_t.key() << ", " << pair_t.value();
}
#endif
