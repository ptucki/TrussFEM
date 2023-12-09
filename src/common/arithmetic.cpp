#include "arithmetic.h"

template<>
bool equals<float>(float t1, float t2)
{
  return NearlyEquals<int32_t>(t1, t2);
}

template<>
bool equals<double>(double t1, double t2)
{
  return NearlyEquals<int64_t>(t1, t2);
}

template<>
bool equals<int>(int t1, int t2)
{
  return t1 == t2;
}

template<>
bool equals<long>(long t1, long t2)
{
  return t1 == t2;;
}