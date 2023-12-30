#include "base_command.h"

BaseCommand::BaseCommand(const ValidOptions& valid_options)
  : is_valid_{ true }
  , valid_options_{ valid_options }
, default_option_{ false }
{
  for (auto& valid_option : valid_options)
  {
    if (valid_option.first == "Default") default_option_ = true;
  }

  //Push default option
  if(default_option_)
    options_.emplace_back(std::make_unique<Option>("Default"));
}

void BaseCommand::Reset()
{
  is_valid_ = true;
  options_.clear();

  if (default_option_)
    options_.emplace_back(std::make_unique<Option>("Default"));
}

void BaseCommand::SetError()
{
  is_valid_ = false;
}

bool BaseCommand::IsValid() const
{
  return is_valid_;
}

const std::string& BaseCommand::GetResult() const
{
  return result_;
}

//bool BaseCommand::IsOptionValid(const std::string& option) const
//{
//  for (auto& [name, required_args] : valid_options_)
//  {
//    if (name == option) return true;
//  }
//  return false;
//}

bool BaseCommand::Execute()
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

bool BaseCommand::AreOptionsValid() const
{
  bool is_valid_option{ false };

  for (auto& option : options_)
  {
    is_valid_option = false;
    for (auto& [name, required_args] : valid_options_)
    {
      if (option->GetName() == name && option->GetArgCount() >= required_args)
      {
        //result_ += ("Provided wrong number of arguments for option [" + name + "]");
        is_valid_option = true;
        break;
      }
    }
    if (!is_valid_option)
    {
      result_ += ("Provided wrong number of arguments for option [" + option->GetName() + "]");
      break;
    }
  }
  return is_valid_option;
}

BaseCommand& operator<<(BaseCommand& command, const std::string& token)
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