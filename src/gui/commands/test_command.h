#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

#include "base_command.h"

class TestCommand : public Command<TestCommand>
{
public:
  TestCommand();

  bool OnExecute(Option& current_option) override;

protected:


};


#endif // !TEST_COMMAND_H
