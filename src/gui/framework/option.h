#ifndef COMMAND_LINE_OPTION_H
#define COMMAND_LINE_OPTION_H

#include <string>
#include <queue>

class Option
{
public:

  Option(std::string name);
  virtual ~Option() = default;

  Option& operator<<(const std::string& arg);

  void AddArgument(const std::string& arg);

  std::string PopArg();

  const std::string& GetName() const;
  const size_t GetArgCount() const;

protected:
  std::string name_;
  std::queue<std::string> args_;
};

#endif // !COMMAND_LINE_OPTION_H
