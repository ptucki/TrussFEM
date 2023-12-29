#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <unordered_map>
#include <string>
//#include <string_view>
#include <memory>
#include <array>
#include <iostream>
#include "utilities.h"

class CommandManager;

// -----------------------------------------------------------------------------

class Option
{
public:

  Option(std::string name) : name_{ name } {}

  virtual ~Option() {}

  Option& operator<<(const std::string& arg)
  {
    AddArgument(arg);

    return *this;
  }

  void AddArgument(const std::string& arg) {
    args_.push(arg);
  }

  std::string PopArg()
  {
    std::string arg = std::move(args_.front());
    args_.pop();
    return arg;
  }

  const std::string& GetName() const { return name_; }
  const size_t GetArgCount() const { return args_.size(); }

protected:
  std::string name_;
  std::queue<std::string> args_;
};

// -----------------------------------------------------------------------------
class BaseCommand
{
public:
  virtual ~BaseCommand() = default;

  bool IsValid() { return is_valid_; }

  

  bool IsOptionValid(const std::string& option)
  {
    for (auto& [name, required_args] : valid_options_)
    {
      if (name == option) return true;
    }
    return false;
  }
  //virtual void Reset() = 0;
  virtual bool OnExecute(Option& current_option) = 0;

  bool Execute()
  {
    result_.clear();

    bool valid{ true };
    if (AreOptionsValid())
    {
      for (auto& option : options_)
      {
        if (!OnExecute(*option))
        {
          valid = false;
          break;
        }
      }
    }
    else
    {
      valid = false;
    }

    Reset();

    return valid;
  }

  bool AreOptionsValid() const
  {
    for (auto& option : options_)
    {
      for (auto [name, required_args] : valid_options_)
      {
        if (option->GetName() != name || option->GetArgCount() < required_args)
          return false;
      }
    }
    return true;
  }

  friend BaseCommand& operator<<(BaseCommand& command, const std::string& token)
  {
    if (token.starts_with('-') || token.starts_with("--"))
    {
      auto it = std::find_if(std::begin(command.valid_options_), std::end(command.valid_options_), [&token](auto item)
        {
          return item.first == token;
        });

      if (it != std::end(command.valid_options_))
      {
        command.options_.emplace_back(std::make_unique<Option>(token));
      }
    }
    else
    {
      auto& last_option_ptr = command.options_.back();
      last_option_ptr->AddArgument(token);
    }

    return command;
  }

  const std::string& GetResult() const
  {
    return result_;
  }

protected:
  BaseCommand(std::vector<std::pair<std::string, int>> validOptions)
    : is_valid_{ true }
    , valid_options_{ validOptions }
  {
    
  }

  void Reset()
  {
    is_valid_ = true;
    options_.clear();
  }

  std::string result_;
private:

  void SetError() { is_valid_ = false; }

  bool is_valid_;
  std::vector<std::unique_ptr<Option>> options_;
  std::vector<std::pair<std::string, int>> valid_options_;
};






// -----------------------------------------------------------------------------
template<typename Derived>
class Command : public BaseCommand
{
public:
  Command(const char* name, std::vector<std::pair<std::string, int>> validOptions) : BaseCommand(validOptions) {
    name_id = name;
  }

  virtual bool OnExecute(Option& current_option) = 0;

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

    if (command != nullptr)
    {
      while (tokens.size() > 0)
      {
        *command << tokens.front();;
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

// -----------------------------------------------------------------------------


#endif // !BASE_COMMAND_H
