#include "coord_p.h"

coord_p::coord_p()
{
   pair.first = 0;
   pair.second.x = 0.0;
   pair.second.y = 0.0;
}

coord_p::~coord_p(){ }

void
coord_p::set(uint32_t key, Coord value)
{
   pair.first = key;
   pair.second = value;
}

uint32_t
coord_p::key() const
{
   return pair.first;
}

const uint32_t*
coord_p::key_p() const
{
   return &pair.first;
}

void
coord_p::key(uint32_t k)
{
   pair.first = k;
}

Coord
coord_p::value() const
{
   return pair.second;
}

const Coord*
coord_p::value_p() const
{
   return &pair.second;
}

void
coord_p::value(Coord v)
{
   pair.second = v;
}

bool
coord_p::operator < (const coord_p& pair_t) const
{
   return this->pair.first < pair_t.pair.first;
}

bool
coord_p::operator <= (const coord_p& pair_t) const
{
   return this->pair.first <= pair_t.pair.first;
}

bool
coord_p::operator > (const coord_p& pair_t) const
{
   return this->pair.first > pair_t.pair.first;
}

bool
coord_p::operator >= (const coord_p& pair_t) const
{
   return this->pair.first >= pair_t.pair.first;
}

bool
coord_p::operator == (const coord_p& pair_t) const
{
   return this->pair.first == pair_t.pair.first;
}

bool
coord_p::operator != (const coord_p& pair_t) const
{
   return this->pair.first != pair_t.pair.first;
}
