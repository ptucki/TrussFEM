#include "cls_command.h"

const ValidOptions valid_options = {
  { "Default", 0 }
};

ClsCommand::ClsCommand(std::list<std::string>& cli_buffer)
  : Command<ClsCommand>("cls", valid_options)
  , cli_buffer_{ cli_buffer }
{

}

bool ClsCommand::OnExecute(Option& current_option)
{
  if (current_option.GetName() == "Default")
  {
    cli_buffer_.clear();
  }

  return true;
}
