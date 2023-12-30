#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include "command_manager_base.h"
#include "comp/log_window.h"
#include "test_command.h"
#include "cls_command.h"
#include "truss_app.h"

class CmdManager : public CommandManagerBase<CmdManager>
{
public:
  void Init(TrussApp* app)
  {
    app_ = app;
    
    auto& component_mng = app->GetComponentManager();
    auto& current_project = *app->GetProject();

    //Init cls command
    auto log_window = component_mng.GetComponentByType<LogWindow>();

    this->AddCommand<ClsCommand>(log_window.lock()->GetResource_ConsoleLogBuffer());

    //Init Test command
    this->AddCommand<TestCommand>();

    //this->AddCommand<ShutdownCommand>();
  }

protected:

  CmdManager()
  {

  }



  friend CommandManagerBase<CmdManager>;
private:
  TrussApp* app_;
};


#endif // !COMMAND_MANAGER_H
