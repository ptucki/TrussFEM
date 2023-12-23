#ifndef UTILITIES_H
#define UTILITIES_H

#include <array>
#include <algorithm>
#include <concepts>
#include <iostream>
#include <string_view>
#include <string>
#include <format>
#include "arithmetic.h"
#include "debug.h"

template<class T>
concept string_like = std::is_convertible_v<T, std::string_view>;

template<class T>
concept not_string_like = !std::is_convertible_v<T, std::string_view>;


template<arithmetic T, arithmetic U, std::size_t N>
constexpr std::array<T, N> SumArrays(std::array<T, N> array1, std::array<U, N> array2)
{
  auto it_arr2 = std::begin(array2);

  for (auto& el : array1) el += *it_arr2++;

  return array1;
}

template<arithmetic T, arithmetic U, std::size_t N>
constexpr std::array<T, N> SubtractArrays(std::array<T, N> array1, std::array<U, N> array2)
{
  auto it_arr2 = std::begin(array2);

  for (auto& el : array1) el -= *it_arr2++;

  return array1;
}

template<typename T, std::size_t N, std::size_t M>
constexpr std::array<T, N+M> ConcatArrays(std::array<T, N> array1, std::array<T, M> array2)
{
  std::array<T, N + M> temp;
  memcpy(temp.data(), array1.data(), N * sizeof(T));
  memcpy(temp.data() + N, array2.data(), M * sizeof(T));
  return temp;
}

template<typename T, std::size_t N>
constexpr decltype(auto) StringifyArrayItems(const std::array<T, N> array)
{
  std::array<std::string, N> temp;

  auto it = std::begin(temp);
  for (const auto& el : array)
  {
    *it = std::to_string(el);
    it++;
  }

  return temp;
}

template<typename T, std::size_t N, typename... Args>
constexpr decltype(auto) StringifyArrayItems(const std::array<T, N> array, const std::format_string<T, Args...> fmt, Args... args)
{
  std::array<std::string, N> temp;

  auto it = std::begin(temp);
  for (const auto& el : array)
  {
    *it = std::vformat(fmt.get(), std::make_format_args(el, args...));
    it++;
  }

  return temp;
}

template<typename Container1, typename Container2, typename BinaryFunction>
constexpr void ForEachCorresponingItems(Container1&& container1, Container2&& container2, BinaryFunction function)
{
  auto first1 = std::begin(std::forward<Container1>(container1));
  auto first2 = std::begin(std::forward<Container2>(container2));
  auto end1 =   std::end(std::forward<Container1>(container1));
  auto end2 =   std::end(std::forward<Container2>(container2));

  for (; first1 != end1 && first2 != end2; first1++, first2++)
  {
    function(*first1, *first2);
  }
}

template<typename R, typename ...Args>
constexpr auto ArgsCount(R(*)(Args ...))
{
  return sizeof...(Args);
}

template<typename R, typename T, typename ...Args>
constexpr auto ArgsCount(R(T::*)(Args ...))
{
  return sizeof...(Args);
}

template<typename R, typename T, typename ...Args>
constexpr auto ArgsCount(R(T::*)(Args ...) const)
{
  return sizeof...(Args);
}

template<typename F>
constexpr auto ArgsCount(F)
{
  return argsCount(&F::operator());
}

constexpr bool IsSpace(char ch);

std::vector<std::string> SplitString(const std::string& str, char splitter, bool ignore_whitespaces = true);

std::vector<double> ConvertStringListToFloats(const std::vector<std::string>& str_floats);

template<typename E>
decltype(auto) ToUnderlying(E enumeration)
{
  return std::underlying_type_t<E>(enumeration);
}

#endif // !UTILITIES_H
