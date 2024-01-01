#include "cs_command.h"

const ValidOptions valid_options = {
  { "Default", 0 },
  { "-n", 3 },
  { "-r", 0 }
};

CordSysCommand::CordSysCommand(std::weak_ptr<Project> project)
  : Command<CordSysCommand>("cs", valid_options)
  , current_project_{ project }
{

}

bool CordSysCommand::OnExecute(Option& current_option)
{

  if (!current_project_.expired())
  {
    auto& project = *current_project_.lock();
    auto option = current_option.GetName();

    if (option == "-n")
    {
      auto x = stod(current_option.PopArg());
      auto y = stod(current_option.PopArg());
      auto z = stod(current_option.PopArg());
      project.SetLocalCoordinateSystem({x, y, z}, {0,0,0});

      result_ = "Changed reference point of coordinate system.";
    }
    else if (option == "-r")
    {
      project.SetLocalCoordinateSystem({ 0, 0, 0 }, { 0,0,0 });
    }
  }

  return true;
}
