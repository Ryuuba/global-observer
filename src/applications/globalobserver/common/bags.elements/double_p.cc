#include "double_p.h"

double_p::double_p()
{
   pair.first = 0;
   pair.second = 0.0;
}

double_p::~double_p(){}

void
double_p::set(uint32_t key, double value)
{
   pair.first = key;
   pair.second = value;
}

uint32_t
double_p::key() const
{
   return pair.first;
}

const uint32_t*
double_p::key_p() const
{
   return &pair.first;
}

void
double_p::key(uint32_t k)
{
   pair.first = k;
}

double
double_p::value() const
{
   return pair.second;
}

const double*
double_p::value_p() const
{
   return &pair.second;
}

void
double_p::value(double v)
{
   pair.second = v;
}

bool
double_p::operator < (const double_p& pair_t) const
{
   return this->pair.second < pair_t.pair.second;
}

bool
double_p::operator <= (const double_p& pair_t) const
{
   return this->pair.second <= pair_t.pair.second;
}

bool
double_p::operator > (const double_p& pair_t) const
{
   return this->pair.second > pair_t.pair.second;
}

bool
double_p::operator >= (const double_p& pair_t) const
{
   return this->pair.second >= pair_t.pair.second;
}

bool
double_p::operator == (const double_p& pair_t) const
{
   return this->pair.second == pair_t.pair.second;
}

bool
double_p::operator != (const double_p& pair_t) const
{
   return this->pair.second != pair_t.pair.second;
}
