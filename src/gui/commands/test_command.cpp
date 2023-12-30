#include "test_command.h"

const ValidOptions valid_options = {
  {"Default", 2 },
  {"-a", 2 }
};

TestCommand::TestCommand()
  : Command<TestCommand>("test", valid_options)
{

}

bool TestCommand::OnExecute(Option& current_option) {

  auto& option = current_option.GetName();

  if (option == "Default")
  {

  }
  else if (option == "-a")
  {
    int a1 = stoi(current_option.PopArg());
    int a2 = stoi(current_option.PopArg());

    result_ += std::to_string(a1 + a2);
  }

  return true;
}
