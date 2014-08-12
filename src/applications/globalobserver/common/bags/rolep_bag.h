#ifndef ROLEP_BAG_H
#define ROLEP_BAG_H
#include <iostream>
#include <string>
#include <set>
#include "role_p.h"

class rolep_bag
{

   protected:
      std::multiset<role_p> bag;
   public:
      typedef std::multiset<role_p>::
              iterator iterator;
      typedef std::multiset<role_p>::
              const_iterator const_iterator;
      rolep_bag();
      virtual ~rolep_bag();
      virtual iterator insert(role_p pair_t);
      virtual iterator insert(uint32_t id, Role r);
      virtual iterator erase(iterator it);
      virtual iterator begin();
      virtual iterator max();
      virtual iterator end();
      virtual unsigned int count(role_p pair_t);
      virtual unsigned int size();
      virtual void clear();
};

std::ostream&
operator << (std::ostream& os, rolep_bag& bag);

#endif
