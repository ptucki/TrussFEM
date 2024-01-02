#ifndef CS_COMMAND_H
#define CS_COMMAND_H

#include "base_command.h"
#include "project.h"
#include "truss_app.h"

class CordSysCommand : public Command<CordSysCommand>
{
public:
  CordSysCommand(std::weak_ptr<Project> project, TrussApp* app);
protected:
  bool OnExecute(Option& current_option) override;
private:
  std::weak_ptr<Project> current_project_;
  TrussApp* app_;
};


#endif // !CLS_COMMAND_H
