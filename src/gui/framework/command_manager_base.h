#ifndef COMMAND_MANAGEER_BASE_H
#define COMMAND_MANAGEER_BASE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <type_traits>
#include <utility>
#include "base_command.h"

class QuickCommand;
class BaseCommand;

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

  void AddQuickCommand(const char* invoker, const std::function<bool(std::string&)>& callable)
  {
    assert(commands_.find(invoker) == commands_.end());

    commands_.insert(
      std::make_pair(invoker, std::make_shared<QuickCommand>(invoker, callable))
    );
  }

  std::weak_ptr<BaseCommand> ParseCommand(const std::string& str) {
    auto tokens = SplitStringIntoQueue(str, ' ', false);

    std::shared_ptr<BaseCommand> command = commands_[tokens.front()];
    tokens.pop();

    if (command != nullptr)
    {
      while (tokens.size() > 0)
      {
        *command << tokens.front();
        tokens.pop();
      }
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

#endif // !COMMAND_MANAGEER_BASE_H
