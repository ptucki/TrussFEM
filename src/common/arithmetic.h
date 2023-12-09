#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <functional>
#include <concepts>
#include <cassert>
#include <iostream>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template<arithmetic T, typename Predicate>
constexpr bool CompareArithmeticTypes(T t1, T t2, Predicate p)
{
  return p(t1, t2);
}

template<typename T>
bool equals(T t1, T t2)
{
  return false;
}

template<>
bool equals<int>(int t1, int t2);

template<>
bool equals<float>(float t1, float t2);

template<>
bool equals<long>(long t1, long t2);

template<>
bool equals<double>(double t1, double t2);


template<std::floating_point T>
decltype(auto) RelativeDifference(T a, T b)
{
  return std::abs((a - b) / (std::min)(a, b));
}

template<std::floating_point T>
decltype(auto) EpsilonDifference(T a, T b, T epsilon = std::numeric_limits<T>::epsilon())
{
  return RelativeDifference(a, b) / epsilon;
}

template<std::integral T, std::floating_point U>
decltype(auto) FloatToRawInt(U f)
{
  static_assert(sizeof(T) == sizeof(U), "Types of T and U have to be same size.");
  T r;
  memcpy(&r, &f, sizeof(f));
  return r;
}

template<std::integral T , std::floating_point U>
T UlpsDistance(const U a, const U b)
{
  static_assert(sizeof(T) == sizeof(U), "Types of T and U have to be same size.");
  if (a == b) return static_cast<T>(0);

  constexpr T max = (std::numeric_limits<T>::max)();

  if (std::isnan(a) || std::isnan(b)) return max;
  if (std::isinf(a) || std::isinf(b)) return max;

  T a_int = FloatToRawInt<T, U>(a);
  T b_int = FloatToRawInt<T, U>(b);

  if (std::signbit(a) != std::signbit(a)) return max;

  T distance = a_int - b_int;
  if (distance < 0) distance = -distance;
  return static_cast<T>(distance);
}

template<std::integral T, std::floating_point U>
bool NearlyEquals(U a, U b, U fixed_epsilon = std::numeric_limits<U>::epsilon(), T ulps_epsilon = 10)
{
  static_assert(sizeof(T) == sizeof(U), "Types of T and U have to be same size.");
  auto difference = std::abs(a - b);
  if (difference <= fixed_epsilon) return true;

  return (UlpsDistance<T, U>(a, b) <= ulps_epsilon);

}

template<std::integral T, std::floating_point U>
T FloatToNativeSignedUlps(U f)
{
  static_assert(sizeof(T) == sizeof(U), "Types of T and U have to be same size.");
  T i;
  memcpy(&i, &f, sizeof(U));

  return i >= 0 ? i : -(i & ~(1<<31));
}

template<std::integral T, std::floating_point U>
U NativeSignedUlpsToFloat(T ulps)
{
  if (ulps < 0) {
    ulps = -ulps;
    ulps |= (1 << 31);
  }
  float f;
  memcpy(&f, &ulps, sizeof(float));
  return f;
}

template<std::integral T, std::floating_point U>
U UlpsIncrement(U f, T ulps)
{
  static_assert(sizeof(T) == sizeof(U), "Types of T and U have to be same size.");
  if (std::isnan(f) || std::isinf(f)) return f;
  auto i = FloatToNativeSignedUlps<T, U>(f);
  i += ulps;
  return NativeSignedUlpsToFloat<T, U>(i);
}

template<std::integral T, std::floating_point U>
U NextFloat(U f)
{
  if (std::isnan(f) || std::isinf(f)) return f;
  auto i = FloatToNativeSignedUlps<T, U>(f);
  i++;
  return NativeSignedUlpsToFloat<T, U>(i);
}



#endif // !ARITHMETIC_H
