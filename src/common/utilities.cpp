#include "Utilities.h"
#include <cctype>
#include <string>

#define WHITESPACES_CHARS " \f\n\r\t\v"

constexpr bool IsSpace(char ch)
{
  return static_cast<int>(ch) <= 32;
}

std::vector<std::string> SplitString(const std::string& str, char splitter, bool ignore_whitespaces)
{
  std::vector<std::string> tokens;
  tokens.reserve(10);

  std::string temp = "";

  for (auto ch : str)
  {
    if (ignore_whitespaces && IsSpace(ch)) continue;
    if (ch == splitter)
    {
      if (!temp.empty()) tokens.push_back(temp);
      temp.resize(0);
      continue;
    }
    temp.append(1, ch);
  }

  if (!temp.empty()) tokens.push_back(temp);
  return tokens;
}

std::queue<std::string> SplitStringIntoQueue(const std::string& str, char splitter, bool ignore_whitespaces)
{
  std::queue<std::string> tokens;

  std::string temp = "";

  for (auto ch : str)
  {
    if (ignore_whitespaces && IsSpace(ch)) continue;
    if (ch == splitter)
    {
      if (!temp.empty()) tokens.push(temp);
      temp.resize(0);
      continue;
    }
    temp.append(1, ch);
  }

  if (!temp.empty()) tokens.push(temp);
  return tokens;
}

std::vector<double> ConvertStringListToFloats(const std::vector<std::string>& str_floats)
{
  std::vector<double> temp;

  temp.reserve(str_floats.size());

  for (const auto& str : str_floats)
  {
    temp.push_back(std::stod(str));
  }

  return temp;
}
