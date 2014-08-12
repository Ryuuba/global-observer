#include "role_p.h"

role_p::role_p()
{
   pair.first = 0;
   pair.second = Role::UNCLUSTERED;
}

role_p::~role_p(){ }

void
role_p::set(uint32_t key, Role value)
{
   pair.first = key;
   pair.second = value;
}

uint32_t
role_p::key() const
{
   return pair.first;
}

const uint32_t*
role_p::key_p() const
{
   return &pair.first;
}

void
role_p::key(uint32_t k)
{
   pair.first = k;
}

Role
role_p::value() const
{
   return pair.second;
}

const Role*
role_p::value_p() const
{
   return &pair.second;
}

void
role_p::value(Role v)
{
   pair.second = v;
}

bool
role_p::operator < (const role_p& pair_t) const
{
   return this->pair.second < pair_t.pair.second;
}

bool
role_p::operator <= (const role_p& pair_t) const
{
   return this->pair.second <= pair_t.pair.second;
}

bool
role_p::operator > (const role_p& pair_t) const
{
   return this->pair.second > pair_t.pair.second;
}

bool
role_p::operator >= (const role_p& pair_t) const
{
   return this->pair.second >= pair_t.pair.second;
}

bool
role_p::operator == (const role_p& pair_t) const
{
   return this->pair.second == pair_t.pair.second;
}

bool
role_p::operator != (const role_p& pair_t) const
{
   return this->pair.second != pair_t.pair.second;
}
