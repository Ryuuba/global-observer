#include "uint8_p.h"

uint8_p::uint8_p()
{
   pair.first = 0;
   pair.second = 0;
}

uint8_p::~uint8_p(){ }

void
uint8_p::set(uint32_t key, uint8_t value)
{
   pair.first = key;
   pair.second = value;
}

uint32_t
uint8_p::key() const
{
   return pair.first;
}

const uint32_t*
uint8_p::key_p() const
{
   return &pair.first;
}

void
uint8_p::key(uint32_t k)
{
   pair.first = k;
}

uint8_t
uint8_p::value() const
{
   return pair.second;
}

const uint8_t*
uint8_p::value_p() const
{
   return &pair.second;
}

void
uint8_p::value(uint8_t v)
{
   pair.second = v;
}

bool
uint8_p::operator < (const uint8_p& pair_t) const
{
   return this->pair.second < pair_t.pair.second;
}

bool
uint8_p::operator <= (const uint8_p& pair_t) const
{
   return this->pair.second <= pair_t.pair.second;
}

bool
uint8_p::operator > (const uint8_p& pair_t) const
{
   return this->pair.second > pair_t.pair.second;
}

bool
uint8_p::operator >= (const uint8_p& pair_t) const
{
   return this->pair.second >= pair_t.pair.second;
}

bool
uint8_p::operator == (const uint8_p& pair_t) const
{
   return this->pair.second == pair_t.pair.second;
}

bool
uint8_p::operator != (const uint8_p& pair_t) const
{
   return this->pair.second != pair_t.pair.second;
}
