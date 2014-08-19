#ifndef SIMTIMEP_BAG_H
#define SIMTIMEP_BAG_H
#include <iostream>
#include <string>
#include <set>
#include "simtime_p.h"

class simtimep_bag
{

   protected:
      std::multiset<simtime_p> bag;
   public:
      typedef std::multiset<simtime_p>::
              iterator iterator;
      typedef std::multiset<simtime_p>::
              const_iterator const_iterator;
      simtimep_bag();
      virtual ~simtimep_bag();
      virtual iterator insert(simtime_p pair_t);
      virtual iterator insert(uint32_t id, simtime_t time);
      virtual iterator erase(iterator it);
      virtual iterator begin() const;
      virtual iterator max() const;
      virtual iterator end() const;
      virtual unsigned int count(simtime_p pair_t);
      virtual unsigned int size();
      virtual void clear();
      virtual bool empty() const;
};

std::ostream&
operator << (std::ostream& os, simtimep_bag& bag);

#endif
