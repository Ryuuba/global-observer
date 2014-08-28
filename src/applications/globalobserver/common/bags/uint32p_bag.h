#ifndef _UINT32P_BAG_H
#define _UINT32P_BAG_H
#include <iostream>
#include <string>
#include <set>
#include "uint32_p.h"

class uint32p_bag
{

   protected:
      std::multiset<uint32_p> bag;
   public:
      typedef std::multiset<uint32_p>::iterator iterator;
      typedef std::multiset<uint32_p>::const_iterator const_iterator;
      uint32p_bag();
      virtual ~uint32p_bag();
      virtual iterator insert(uint32_p pair_t);
      virtual iterator insert(uint32_t id, uint32_t v);
      virtual iterator erase(iterator it);
      virtual iterator begin() const;
      virtual iterator max() const;
      virtual iterator end() const;
      virtual unsigned int count(uint32_p pair_t);
      virtual unsigned int size();
      virtual void clear();
      virtual bool empty() const;
      virtual std::pair<iterator,iterator>
      equalRange(uint32_t v) const;
};

std::ostream&
operator << (std::ostream& os, uint32p_bag& bag);

#endif
