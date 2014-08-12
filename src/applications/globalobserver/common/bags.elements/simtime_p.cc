#include "simtime_p.h"

simtime_p::simtime_p()
{
   pair.first = 0;
   pair.second = 0;
}

simtime_p::~simtime_p(){ }

void
simtime_p::set(uint32_t key, simtime_t value)
{
   pair.first = key;
   pair.second = value;
}

uint32_t
simtime_p::key() const
{
   return pair.first;
}

const uint32_t*
simtime_p::key_p() const
{
   return &pair.first;
}

void
simtime_p::key(uint32_t k)
{
   pair.first = k;
}

simtime_t
simtime_p::value() const
{
   return pair.second;
}

const simtime_t*
simtime_p::value_p() const
{
   return &pair.second;
}

void
simtime_p::value(simtime_t v)
{
   pair.second = v;
}

bool
simtime_p::operator < (const simtime_p& pair_t) const
{
   return this->pair.second < pair_t.pair.second;
}

bool
simtime_p::operator <= (const simtime_p& pair_t) const
{
   return this->pair.second <= pair_t.pair.second;
}

bool
simtime_p::operator > (const simtime_p& pair_t) const
{
   return this->pair.second > pair_t.pair.second;
}

bool
simtime_p::operator >= (const simtime_p& pair_t) const
{
   return this->pair.second >= pair_t.pair.second;
}

bool
simtime_p::operator == (const simtime_p& pair_t) const
{
   return this->pair.second == pair_t.pair.second;
}

bool
simtime_p::operator != (const simtime_p& pair_t) const
{
   return this->pair.second != pair_t.pair.second;
}
