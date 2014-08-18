#ifndef UINT8P_BAG_H
#define UINT8P_BAG_H
#include <iostream>
#include <string>
#include <set>
#include "uint8_p.h"

class uint8p_bag
{

   protected:
      std::multiset<uint8_p> bag;
   public:
      typedef std::multiset<uint8_p>::
              iterator iterator;
      typedef std::multiset<uint8_p>::
              const_iterator const_iterator;
      uint8p_bag();
      virtual ~uint8p_bag();
      virtual iterator insert(uint8_p pair_t);
      virtual iterator insert(uint32_t id, uint8_t v);
      virtual iterator erase(iterator it);
      virtual iterator begin() const;
      virtual iterator max() const;
      virtual iterator end() const;
      virtual unsigned int count(uint8_p pair_t);
      virtual unsigned int size();
      virtual void clear();
      virtual bool empty();
};

std::ostream&
operator << (std::ostream& os, uint8p_bag& bag);

#endif
