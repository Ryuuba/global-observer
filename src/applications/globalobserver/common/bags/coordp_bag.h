#ifndef COORDP_BAG_H
#define COORD2P_BAG_H
#include <iostream>
#include <string>
#include <set>
#include "coord_p.h"

class coordp_bag
{

   protected:
      std::multiset<coord_p> bag;
   public:
      typedef std::multiset<coord_p>::
              iterator iterator;
      typedef std::multiset<coord_p>::
              const_iterator const_iterator;
      coordp_bag();
      virtual ~coordp_bag();
      virtual iterator insert(coord_p pair_t);
      virtual iterator insert(uint32_t id, Coord position);
      virtual iterator erase(iterator it);
      virtual iterator begin();
      virtual iterator max();
      virtual iterator end();
      virtual unsigned int count(coord_p pair_t);
      virtual unsigned int size();
      virtual void clear();
};

std::ostream&
operator << (std::ostream& os, coordp_bag& bag);

#endif
