#ifndef ROLE_H_INCLUDED
#define ROLE_H_INCLUDED
#include <iostream>

enum class Role : uint8_t
{
    UNCLUSTERED = 0,
    CLUSTERED = 1,
    GATEWAY = 2,
    LEADER = 3
};

inline std::ostream&
operator << (std::ostream& os, const Role r)
{
   std::string buffer;
   if ( r == Role::UNCLUSTERED)
      buffer = "UNCLUSTERED";
   else if ( r == Role::CLUSTERED)
      buffer = "CLUSTERED";
   else if ( r == Role::GATEWAY)
      buffer = "GATEWAY";
   else
      buffer = "LEADER";
   return os << buffer;
}

#endif // ROLE_H_INCLUDED
