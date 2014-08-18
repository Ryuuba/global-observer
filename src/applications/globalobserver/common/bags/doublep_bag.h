#ifndef DOUBLEP_BAG_H
#define DOUBLEP_BAG_H
#include <iostream>
#include <string>
#include <set>
#include "double_p.h"

class doublep_bag
{

   protected:
      std::multiset<double_p> bag;
   public:
      typedef std::multiset<double_p>::
              iterator iterator;
      typedef std::multiset<double_p>::
              const_iterator const_iterator;
      doublep_bag();
      virtual ~doublep_bag();
      virtual iterator insert(double_p pair_t);
      virtual iterator insert(uint32_t id, double speed);
      virtual iterator erase(iterator it);
      virtual iterator begin() const;
      virtual iterator max() const;
      virtual iterator end() const;
      virtual unsigned int count(double_p pair_t);
      virtual unsigned int size();
      virtual void clear();
      virtual bool empty();
};

std::ostream&
operator << (std::ostream& os, doublep_bag& bag);

#endif
