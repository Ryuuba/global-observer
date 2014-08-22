#ifndef ROLE_P_H
#define ROLE_P_H
#include <iostream>
#include <cstdint>
#include <utility>
#include "role.h"

// par <key,value>. comparisons are performed considering
// the value

class role_p
{
   public:
      role_p();
      virtual ~role_p();
      virtual void set(uint32_t key, Role value);
      virtual uint32_t key() const;
      virtual const uint32_t* key_p() const;
      virtual void key(uint32_t k);
      virtual Role value() const;
      virtual const Role* value_p() const;
      virtual void value(Role v);
      virtual bool operator <(const role_p& pair_t) const;
      virtual bool operator <=(const role_p& pair_t) const;
      virtual bool operator >(const role_p& pair_t) const;
      virtual bool operator >=(const role_p& pair_t) const;
      virtual bool operator ==(const role_p& pair_t) const;
      virtual bool operator !=(const role_p& pair_t) const;
   protected:
      std::pair<uint32_t,Role> pair;
};

inline std::ostream&
operator << (std::ostream& os, const role_p& pair_t)
{
   std::string buffer;
   if ( pair_t.value() == Role::UNCLUSTERED)
      buffer = "UNCLUSTERED";
   else if ( pair_t.value() == Role::CLUSTERED)
      buffer = "CLUSTERED";
   else if ( pair_t.value() == Role::GATEWAY)
      buffer = "GATEWAY";
   else
      buffer = "LEADER";
   return os << pair_t.key() << ", "
             << buffer;
}

#endif
