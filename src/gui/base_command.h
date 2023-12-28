#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <unordered_map>
#include <string>
//#include <string_view>
#include <memory>
#include <iostream>
#include "utilities.h"

class CommandManager;

// -----------------------------------------------------------------------------
class BaseCommand
{
public:
  virtual bool Execute() = 0;
  virtual ~BaseCommand() = default;



protected:
  BaseCommand()
    : expected_args_{ 0 }
    , is_valid_{ true }
  {
  
  }

  BaseCommand& operator<<(const std::string& token)
  {
    if (token.starts_with('-') || token.starts_with("--"))
    {
      expected_args_ = this->ProvideOption(token);
    }
    else if(expected_args_ > 0)
    {
      this->ProvideArgument(token);
      expected_args_--;
    }
    else
    {
      SetError();
    }

    return *this;
  }

  virtual int ProvideOption(const std::string& token) = 0;
  virtual void ProvideArgument(const std::string& token) = 0;


private:

  void SetError() { is_valid_ = false; }

  int expected_args_;
  bool is_valid_;
};

// -----------------------------------------------------------------------------
template<typename Derived>
class Command : public BaseCommand
{
public:
  Command(const char* name) : BaseCommand() {
    name_id = name;
  }

  virtual bool Execute() override = 0;

  static const std::string& GetInvoker() { return name_id; }

private:
  static std::string name_id;
};

template<typename Derived>
std::string Command<Derived>::name_id = "";

// -----------------------------------------------------------------------------
template<class Derived>
class CommandManagerBase
{
public:
  using CommandMap = std::unordered_map<std::string, std::shared_ptr<BaseCommand>>;

  decltype(auto) Request(const std::string& command)
  {
    return ParseCommand(command);
  }

  static Derived& GetInstance()
  {
    static Derived instance;
    return instance;
  }

  template<class Command>
  std::weak_ptr<Command> Get()
  {
    return std::static_pointer_cast<Command>(
      commands_[Command::GetName()]
    );
  }

  std::weak_ptr<BaseCommand> GetCommand(const std::string& name)
  {
    return commands_[name];
  }

protected:
  CommandManagerBase() = default;

  CommandManagerBase(const CommandManagerBase&) = delete;
  CommandManagerBase(CommandManagerBase&&) = delete;
  CommandManagerBase& operator=(const CommandManagerBase&) = delete;
  CommandManagerBase& operator=(CommandManagerBase&&) = delete;
  virtual ~CommandManagerBase() = default;

  template<class Command, typename... Args>
    requires std::is_base_of<BaseCommand, Command>::value
  void AddCommand(Args&&... args)
  {
    commands_.insert(
      std::make_pair(Command::GetInvoker(), std::make_shared<Command>(std::forward<Args>(args)...))
    );
  }

  std::weak_ptr<BaseCommand> ParseCommand(const std::string& str) {
    auto tokens = SplitStringIntoQueue(str, ' ', false);

    std::shared_ptr<BaseCommand> command = commands_[tokens.front()];
    tokens.pop();

    while (tokens.size() > 0)
    {
      command << tokens.front();;
      tokens.pop();
    }

    return command;
  }

  static bool isOption(const std::string& token)
  {
    return token.starts_with('-') || token.starts_with("--");
  }

private:
  CommandMap commands_;
  static Derived* instance;
};

// -----------------------------------------------------------------------------


#endif // !BASE_COMMAND_H
