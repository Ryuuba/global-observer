#ifndef DOUBLE_P_H
#define DOUBLE_P_H
#include <iostream>
#include <cstdint>
#include <utility>

class double_p
{
   protected:
      std::pair<uint32_t,double> pair;
   public:
      double_p();
       ~double_p();
      virtual void set(uint32_t key, double value);
      virtual uint32_t key() const;
      virtual const uint32_t* key_p() const;
      virtual void key(uint32_t k);
      virtual double value() const;
      virtual const double* value_p() const;
      virtual void value(double v);
      virtual bool operator < (const double_p& pair_t) const;
      virtual bool operator <= (const double_p& pair_t) const;
      virtual bool operator > (const double_p& pair_t) const;
      virtual bool operator >= (const double_p& pair_t) const;
      virtual bool operator == (const double_p& pair_t) const;
      virtual bool operator != (const double_p& pair_t) const;
};

inline std::ostream&
operator << (std::ostream& os, double_p& pair_t)
{
   return os << pair_t.key() << ", " << pair_t.value();
}

#endif
