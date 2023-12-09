#ifndef DEBUG_H
#define DEBUG_H
#ifdef _DEBUG

#include <string_view>

#  define PRINT_TYPE(x) std::cout << #x <<"[" << TypeName<decltype(x)>() <<"]\n"

template <class T>
constexpr std::string_view TypeName()
{
#ifdef __clang__
  std::string_view p = __PRETTY_FUNCTION__;
  return std::string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
  std::string_view p = __PRETTY_FUNCTION__;
#if __cplusplus < 201402
  return std::string_view(p.data() + 36, p.size() - 36 - 1);
#else
  return std::string_view(p.data() + 49, p.find(';', 49) - 49);
#endif
#elif defined(_MSC_VER)
  std::string_view p = __FUNCSIG__;
  return std::string_view(p.data() + 83, p.size() - 83 - 7);
#endif
}

#else // !_DEBUG
#  define PRINT_TYPE(x) (void)0

#endif // !_DEBUG
#endif // !DEBUG_H
