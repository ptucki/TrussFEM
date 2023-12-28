#ifndef COMMAND_H
#define COMMAND_H

#include "base_command.h"

class TestCommand : public Command<TestCommand>
{
public:
  TestCommand() : Command<TestCommand>("test") {
    std::cout << "Command Added!\n";
  }

  bool Execute() override {
    std::cout << "Execute <test>!\n";
    return true;
  }
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