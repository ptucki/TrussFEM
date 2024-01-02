#include "cs_command.h"
#include "comp/workspace.h"

const ValidOptions valid_options = {
  { "Default", 0 },
  { "-n", 3 },
  { "-r", 0 }
};

CordSysCommand::CordSysCommand(std::weak_ptr<Project> project, TrussApp* app)
  : Command<CordSysCommand>("cs", valid_options)
  , current_project_{ project }
  , app_{ app }
{

}

bool CordSysCommand::OnExecute(Option& current_option)
{

  if (!current_project_.expired())
  {
    auto comp_mng = app_->GetComponentManager();
    auto workspace = comp_mng.GetComponentByType<Workspace>();

    auto& project = *current_project_.lock();
    auto option = current_option.GetName();

    if (option == "-n")
    {
      auto x = stod(current_option.PopArg());
      auto y = stod(current_option.PopArg());
      auto z = stod(current_option.PopArg());
      project.SetLocalCoordinateSystem({ x, y, z }, { 0,0,0 });

      result_ = "Changed reference point of coordinate system.";
    }
    else if (option == "-r")
    {
      project.SetLocalCoordinateSystem({ 0, 0, 0 }, { 0,0,0 });
    }

    auto& workspace_obj = *workspace.lock();
    workspace_obj.Action_PrepareDataToDisplay();
  }

  return true;
}
