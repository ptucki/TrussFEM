#ifndef POINT_H
#define POINT_H

#include <concepts>
#include <initializer_list>
#include <array>
#include <functional>
#include <span>
#include <iostream>
#include <utility>
#include "utilities.h"
#include "arithmetic.h"

#ifdef _DEBUG
  #define  DEBUG_POINT
#endif // _DEBUG

/**
* @brief Class of N-dimensional representation of Point
*
* @param N point's dimentions
* @param T type of point data
*/
template<int N, arithmetic T = double>
class Point;

using Point2 = Point<2>;
using Point3 = Point<3>;

template<int N, arithmetic T>
class Point
{
  static_assert(N >= 2, "Point must have at least two dimentions.");
public:
  using value_type = T;
  using reference = T&;
  using size_type = decltype(N);

  /**
  * Constructs a new point with coordinates set to 0.
  * @brief Default constructor
  * @see template<arithmetic U, arithmetic... Tail> Point(U arg, Tail... args);
  * @see template<typename Indices = std::make_index_sequence<N>> Point(std::array<T, N> values);
  * @see template<std::size_t... I> Point(std::array<T, N> values, std::index_sequence<I...>);
  */
  Point() noexcept : values_{ 0 } {}

  /**
  * Constructs a new point with given coordinates.
  * @brief Constructor
  * 
  * @param arg - first coordinate
  * @param args - subsequent coordinates
  * 
  * @see Point() noexcept;
  * @see template<typename Indices = std::make_index_sequence<N>> Point(std::array<T, N> values);
  * @see template<std::size_t... I> Point(std::array<T, N> values, std::index_sequence<I...>);
  */
  template<arithmetic U, arithmetic... Tail>
  Point(U arg, Tail... args);

  Point(const Point<N, T>& point);
  Point(Point<N, T>&& point) noexcept;

  /**
  * Constructs a new point with given coordinates.
  * @brief Constructor
  * @see Point() noexcept;
  * @see template<arithmetic U, arithmetic... Tail> Point(U arg, Tail... args);
  * @see template<std::size_t... I> Point(std::array<T, N> values, std::index_sequence<I...>);
  */
  template<typename Indices = std::make_index_sequence<N>>
  Point(std::array<T, N> values);

  /**
  * @brief Get raw pointer to point's data.
  * @return Raw pointer to point's data.
  */
  const T* data() noexcept;

  /**
  * @brief Get const reference to array of point coordinates.
  * @return Const reference to array of point coordinates.
  */
  const std::array<value_type, N>&  GetValues() const&;

  /**
  * @brief Get reference to array of point coordinates.
  * @return Reference to array of point coordinates.
  */
  std::array<value_type, N>&  GetValues() &;

  /**
  * @brief Get value reference to array of point coordinates.
  * @return Value reference to array of point coordinates.
  */
  std::array<value_type, N>&& GetValues() &&;
  
  /**
  * @brief Sets point coordinates for given subsequent arguments.
  * @param U - arithmetic type of first argument
  * @param Args - arithmetic type pack of subsequent parameters
  * @param arg - first argument
  * @param args - subsequent parameters
  */
  template<arithmetic U, arithmetic ...Args>
  void SetValues(U arg, Args... args);

  /**
  * @brief Sets given point coordinate value.
  * @param index - coordinate poisiton
  * @param value - new coordinate value
  */
  void SetValueAt(int index, T value);


  /**
  * @brief Get reference to M point coordinate.
  * @param M - given coordinate
  * @return Reference to M coordinate.
  */
  template<decltype(N) M>
  constexpr reference get();

  /**
  * @brief Get X(at index 0) point coordinate value.
  * @return X coordinate value.
  */
  constexpr value_type GetX() const;

  /**
  * @brief Get Y(at index 1) point coordinate value.
  * @return Y coordinate value.
  */
  constexpr value_type GetY() const;

  /**
  * @brief Get Z(at index 2) point coordinate value.
  * @return Z coordinate value.
  */
  constexpr value_type GetZ() const;

  /**
  * @brief Get dimensions count of a point.
  * @return Number of dimensions of a point.
  */
  static constexpr size_type DimensionCount() noexcept;

  constexpr Point& operator=(const Point& obj);
  constexpr Point& operator=(Point&& obj);

  constexpr Point operator+(Point point);
  constexpr Point& operator+=(Point data);
  constexpr Point operator-(Point point);
  constexpr Point& operator-=(Point data);

  template<arithmetic U>
  constexpr Point operator*(U num);

  template<arithmetic U>
  constexpr Point& operator*=(U num);
  constexpr bool operator==(Point point);
  constexpr bool operator!=(Point point);

  constexpr operator std::array<T,N>();
  
  template<arithmetic U>
  constexpr operator Point<N,U>();

#ifdef DEBUG_POINT
  void Print() const;
#endif
private:

  /**
    * Constructs a new point
    * @brief Constructor
    * @param I - index sequence
    * @param values - point coordinations 
    * @see template<arithmetic U, arithmetic... Tail> Point(U arg, Tail... args);
    * @see template<typename Indices = std::make_index_sequence<N>> Point(std::array<T, N> values);
  */
  template<std::size_t... I>
  Point(std::array<T, N> values, std::index_sequence<I...>) : Point(values[I]...) {}

  std::array<value_type,N> values_; /**< point coordinates */
};

template<int N, arithmetic T>
template<arithmetic U, arithmetic ...Tail>
Point<N, T>::Point(U arg, Tail ...args)
  : values_{ static_cast<value_type>(arg), static_cast<value_type>(args)... }
{

}

template<int N, arithmetic T>
template<typename Indices>
Point<N, T>::Point(std::array<T, N> values) : Point(values, Indices{})
{

}

template<int N, arithmetic T>
inline Point<N, T>::Point(const Point<N, T>& point)
{
  values_ = point.values_;
}

template<int N, arithmetic T>
inline Point<N, T>::Point(Point<N, T>&& point) noexcept
{
  values_ = std::move(point.values_);
}

template<int N, arithmetic T>
const T* Point<N, T>::data() noexcept
{
  return values_.data();
}

template<int N, arithmetic T>
const std::array<T, N>& Point<N, T>::GetValues() const&
{
  return values_;
}

template<int N, arithmetic T>
std::array<T, N>& Point<N, T>::GetValues()&
{
  return values_;
}

template<int N, arithmetic T>
std::array<T, N>&& Point<N, T>::GetValues() &&
{
  return std::move(values_);
}


template<int N, arithmetic T>
inline void Point<N, T>::SetValueAt(int index, T value)
{
  values_[index] = value;
}

template<int N, arithmetic T>
template<arithmetic U, arithmetic ...Args>
inline void Point<N, T>::SetValues(U arg, Args ...args)
{
  static_assert(sizeof...(Args) == N - 1, "Number of arguments must be equal to the number of defined point dimentions");
  std::array<T, sizeof...(Args) + 1> temp = {arg, args...};
  values_ = std::move(temp);
}

template<int N, arithmetic T>
template<decltype(N) M>
constexpr Point<N, T>::reference Point<N, T>::get()
{
  static_assert(M < N, "Cannot get M-coordinate from N-dimensional Point. (M >= N)");

  return values_[M];
}

template<int N, arithmetic T>
template<arithmetic U>
constexpr Point<N, T>::operator Point<N, U>()
{
  Point<N, U> temp;

  ForEachCorresponingItems(temp.GetValues(), this->values_, [](auto& item1, auto& item2) {
    item1 = static_cast<U>(item2);
    });

  return temp;
}

template<int N, arithmetic T>
constexpr Point<N, T>::value_type Point<N, T>::GetX() const
{
  return values_[0];
}

template<int N, arithmetic T>
constexpr Point<N, T>::value_type Point<N, T>::GetY() const
{
  return values_[1];
}

template<int N, arithmetic T>
constexpr Point<N, T>::value_type Point<N, T>::GetZ() const
{
  static_assert(N > 2, "Cannot get z-coordinate from N-dimensional Point.");
  return values_[2];
}

template<int N, arithmetic T>
constexpr Point<N, T>::size_type Point<N, T>::DimensionCount() noexcept
{
  return N;
}

template<int N, arithmetic T>
inline constexpr Point<N,T>& Point<N, T>::operator=(const Point& obj)
{
  this->values_ = obj.values_;

  return *this;
}

template<int N, arithmetic T>
inline constexpr Point<N, T>& Point<N, T>::operator=(Point&& obj)
{
  this->values_ = std::move(obj.values_);

  return *this;
}

template<int N, arithmetic T>
constexpr Point<N, T> Point<N, T>::operator+(Point point)
{
  return Point<N,T>(SumArrays(this->values_, point.values_));
}

template<int N, arithmetic T>
constexpr Point<N, T>& Point<N, T>::operator+=(Point point)
{
  ForEachCorresponingItems(this->values_, point.values_, [](auto& item1, auto& item2) {
    item1 += item2;
    });
  return *this;
}

template<int N, arithmetic T>
constexpr Point<N, T> Point<N, T>::operator-(Point point)
{
  return Point<N,T>(SubtractArrays(this->values_, point.values_));
}

template<int N, arithmetic T>
constexpr Point<N, T>& Point<N, T>::operator-=(Point point)
{
  ForEachCorresponingItems(this->values_, point.values_, [](auto& item1, auto& item2) {
    item1 -= item2;
    });
  return *this;
}

template<int N, arithmetic T>
template<arithmetic U>
constexpr Point<N, T> Point<N, T>::operator*(U num)
{
  for (auto& el : this->values_) el *= num;
  return *this;
}

template<int N, arithmetic T>
template<arithmetic U>
constexpr Point<N, T>& Point<N, T>::operator*=(U num)
{
  for (auto& el : this->values_) el *= num;
  return *this;
}

template<int N, arithmetic T>
constexpr bool Point<N, T>::operator==(Point point)
{
  auto it1 = std::cbegin(values_);
  auto end1 = std::cend(values_);
  auto it2 = std::cbegin(point.values_);
  bool value = true;

  while (it1 != end1)
  {
    value = value && equals(*it1, *it2);
    it1++;
    it2++;
  }

  return value;
}

template<int N, arithmetic T>
constexpr bool Point<N, T>::operator!=(Point point)
{
  auto it1 = std::cbegin(values_);
  auto end1 = std::cend(values_);
  auto it2 = std::cbegin(point.values_);
  bool value = false;

  while (it1 != end1)
  {
    value = value || (!equals(*it1, *it2));
    it1++;
    it2++;
  }

  return value;
}

template<int N, arithmetic T>
constexpr Point<N, T>::operator std::array<T, N>()
{
  return this->values_;
}


/* --- Debug --- */
#ifdef DEBUG_POINT

template<int N, arithmetic T>
void Point<N, T>::Print() const
{
  std::cout << "Point" << "<" << N << "> [";
  for (auto it = values_.cbegin(); it != (values_.cend() - 1); ++it) std::cout << *it << ", ";
  std::cout << *(values_.cend() - 1) << "]\n";
}
#endif

#endif // !POINT_H
