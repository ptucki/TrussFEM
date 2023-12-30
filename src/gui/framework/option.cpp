#include "option.h"

Option::Option(std::string name) : name_{ name } {}

Option& Option::operator<<(const std::string& arg)
{
  AddArgument(arg);

  return *this;
}

void Option::AddArgument(const std::string& arg) {
  args_.push(arg);
}

std::string Option::PopArg()
{
  std::string arg = std::move(args_.front());
  args_.pop();
  return arg;
}

const std::string& Option::GetName() const
{
  return name_;
}

const size_t Option::GetArgCount() const
{
  return args_.size();
}