#include "uint32_p.h"

uint32_p::uint32_p()
{
   pair.first = 0;
   pair.second = 0;
}

uint32_p::~uint32_p(){ }

void
uint32_p::set(uint32_t key, uint32_t value)
{
   pair.first = key;
   pair.second = value;
}

uint32_t
uint32_p::key() const
{
   return pair.first;
}

const uint32_t*
uint32_p::key_p() const
{
   return &pair.first;
}

void
uint32_p::key(uint32_t k)
{
   pair.first = k;
}

uint32_t
uint32_p::value() const
{
   return pair.second;
}

const uint32_t*
uint32_p::value_p() const
{
   return &pair.second;
}

void
uint32_p::value(uint32_t v)
{
   pair.second = v;
}

bool
uint32_p::operator < (const uint32_p& pair_t) const
{
   return this->pair.second < pair_t.pair.second;
}

bool
uint32_p::operator <= (const uint32_p& pair_t) const
{
   return this->pair.second <= pair_t.pair.second;
}

bool
uint32_p::operator > (const uint32_p& pair_t) const
{
   return this->pair.second > pair_t.pair.second;
}

bool
uint32_p::operator >= (const uint32_p& pair_t) const
{
   return this->pair.second >= pair_t.pair.second;
}

bool
uint32_p::operator == (const uint32_p& pair_t) const
{
   return this->pair.second == pair_t.pair.second;
}

bool
uint32_p::operator != (const uint32_p& pair_t) const
{
   return this->pair.second != pair_t.pair.second;
}
