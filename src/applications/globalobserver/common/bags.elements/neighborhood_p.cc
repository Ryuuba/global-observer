#include "neighborhood_p.h"

neighborhood_p::neighborhood_p()
{
   pair.first = 0;
}

neighborhood_p::~neighborhood_p(){}

void
neighborhood_p::set(uint32_t key, Neighborhood& value)
{
   pair.first = key;
   pair.second = value;
}

uint32_t
neighborhood_p::key() const
{
   return pair.first;
}

const uint32_t*
neighborhood_p::key_p() const
{
   return &pair.first;
}

void
neighborhood_p::key(uint32_t k)
{
   pair.first = k;
}

Neighborhood
neighborhood_p::value() const
{
   return pair.second;
}

const Neighborhood*
neighborhood_p::value_p() const
{
   return &pair.second;
}

void
neighborhood_p::insert(Neighborhood::Neighbor neighbor)
{
   pair.second.insert(neighbor);
}

void
neighborhood_p::value(Neighborhood n)
{
   pair.second = n;
}

bool
neighborhood_p::
operator < (const neighborhood_p& pair_t) const
{
   return pair.second.size() < pair_t.pair.second.size();
}

bool
neighborhood_p::
operator <= (const neighborhood_p& pair_t) const
{
   return pair.second.size() <= pair_t.pair.second.size();
}

bool
neighborhood_p::
operator > (const neighborhood_p& pair_t) const
{
   return pair.second.size() > pair_t.pair.second.size();
}


bool
neighborhood_p::
operator >= (const neighborhood_p& pair_t) const
{
   return pair.second.size() >= pair_t.pair.second.size();
}


bool
neighborhood_p::
operator == (const neighborhood_p& pair_t) const
{
   return
   (pair.second == pair_t.pair.second)&&
   (pair.first == pair_t.pair.first);
}

bool
neighborhood_p::
operator != (const neighborhood_p& pair_t) const
{
   return
   !((pair.second == pair_t.pair.second)&&
   (pair.first == pair_t.pair.first));
}
