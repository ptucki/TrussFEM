#ifndef CLS_COMMAND_H
#define CLS_COMMAND_H

#include "base_command.h"

class ClsCommand : public Command<ClsCommand>
{
public:
  ClsCommand(std::list<std::string>& cli_buffer);
protected:
  bool OnExecute(Option& current_option) override;
private:
  std::list<std::string>& cli_buffer_;
};


#endif // !CLS_COMMAND_H
