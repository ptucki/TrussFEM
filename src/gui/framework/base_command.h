#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "utilities.h"
#include "command_manager_base.h"
#include "option.h"

using ValidOptions = std::vector<std::pair<std::string, int>>;

class BaseCommand
{
public:

  virtual ~BaseCommand() = default;

  bool IsValid() const;
  bool IsOptionValid(const std::string& option) const;

  bool Execute();

  friend BaseCommand& operator<<(BaseCommand& command, const std::string& token);

  const std::string& GetResult() const;

protected:

  virtual bool OnExecute(Option& current_option) = 0;
  bool AreOptionsValid() const;
  BaseCommand(const ValidOptions& valid_options);
  void Reset();


  mutable std::string result_;
private:

  void SetError();

  bool is_valid_;
  std::vector<std::unique_ptr<Option>> options_;
  const ValidOptions& valid_options_;
  bool default_option_;
};

template<typename Derived>
class Command : public BaseCommand
{
public:
  Command(const char* name, const ValidOptions& validOptions) : BaseCommand(validOptions) {
    name_id = name;
  }

  static const std::string& GetInvoker() { return name_id; }

protected:
  virtual bool OnExecute(Option& current_option) = 0;

private:
  static std::string name_id;
};

template<typename Derived>
std::string Command<Derived>::name_id = "";

#endif // !BASE_COMMAND_H
