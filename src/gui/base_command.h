#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

class CommandManager;

// -----------------------------------------------------------------------------
class BaseCommand
{
public:
  virtual bool Execute() = 0;

protected:
  BaseCommand() {}

  virtual ~BaseCommand() = default;

private:
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

  //static void ParseCommand() {}

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

private:
  CommandMap commands_;
  static Derived* instance;
};

// -----------------------------------------------------------------------------


#endif // !BASE_COMMAND_H
