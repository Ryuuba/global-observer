#ifndef ROLE_H_INCLUDED
#define ROLE_H_INCLUDED
#include <iostream>

enum class Role : uint8_t
{
   ISOLATED = 0,
   UNCLUSTERED = 1,
   CLUSTERED = 2,
   GATEWAY = 3,
   LEADER = 4
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
   else if ( r == Role::LEADER)
      buffer = "LEADER";
   else
      buffer = "ISOLATED";
   return os << buffer;
}

#endif // ROLE_H_INCLUDED
