#ifndef COMMAND_H
#define COMMAND_H

#include <variant>
#include "base_command.h"

class TestCommand : public Command<TestCommand>
{
public:
  TestCommand()
    : Command<TestCommand>("test", {{"-a", 2}})
  {
    std::cout << "Command Added!\n";
  }

  bool OnExecute(Option& current_option) override {

    if (current_option.GetName() == "-a")
    {
      int a1 = stoi(current_option.PopArg());
      int a2 = stoi(current_option.PopArg());

      result_ += std::to_string(a1 + a2);
    }

    return true;
  }

protected:
};

class CmdManager : public CommandManagerBase<CmdManager>
{
  
protected:
  CmdManager() {
    std::cout << "CmdManager initialized\n";

    this->AddCommand<TestCommand>();
  }

  friend CommandManagerBase<CmdManager>;
};

#endif // !COMMAND_H