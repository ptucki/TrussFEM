#ifndef CS_COMMAND_H
#define CS_COMMAND_H

#include "base_command.h"
#include "project.h"

class CordSysCommand : public Command<CordSysCommand>
{
public:
  CordSysCommand(std::weak_ptr<Project> project);
protected:
  bool OnExecute(Option& current_option) override;
private:
  std::weak_ptr<Project> current_project_;
};


#endif // !CLS_COMMAND_H
