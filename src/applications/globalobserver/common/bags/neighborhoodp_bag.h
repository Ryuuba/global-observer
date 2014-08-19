#ifndef UINT32P_BAG_H
#define UINT32P_BAG_H
#include <iostream>
#include <string>
#include <set>
#include "neighborhood_p.h"

class neighborhoodp_bag
{

   protected:
      std::multiset<neighborhood_p> bag;
   public:
      typedef std::multiset<neighborhood_p>::
              iterator iterator;
      typedef std::multiset<neighborhood_p>::
              const_iterator const_iterator;
      neighborhoodp_bag();
      virtual ~neighborhoodp_bag();
      virtual iterator insert(neighborhood_p pair_t);
      virtual iterator insert(uint32_t id, Neighborhood n);
      virtual iterator erase(iterator it);
      virtual iterator begin();
      virtual iterator begin() const;
      virtual iterator end();
      virtual iterator end() const;
      virtual iterator max();
      virtual iterator max() const;
      virtual unsigned int size();
      virtual unsigned int size() const;
      virtual void clear();
      virtual bool empty() const;
};

std::ostream&
operator <<(std::ostream& os, const neighborhoodp_bag& bag);

#endif
