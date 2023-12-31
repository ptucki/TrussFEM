#include "quick_command.h"

const ValidOptions valid_options = {
  { "Default", 0 }
};

QuickCommand::QuickCommand(const char* invoker, const std::function<bool(std::string&)>& callable)
  : BaseCommand(valid_options)
  , invoker_{ invoker }
  , callable_{ callable }
{

}

bool QuickCommand::OnExecute(Option& current_option)
{
  if (current_option.GetName() == "Default")
  {
    if (current_option.GetArgCount() > 0)
    {
      result_ = "Provided too many arguments.";
    }
    else
    {
      return callable_(result_);
    }
  }

  return false;
}
