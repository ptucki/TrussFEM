#include "truss_app.h"
#include "comp/workspace.h"
#include "comp/log_window.h"
#include "command_manager.h"

#include <iostream>

TrussApp::TrussApp()
  : project_{ std::make_shared<Project>() }
{
  component_manager_.AttachComponent<Workspace>(parent_, project_);
  component_manager_.AttachComponent<LogWindow>(parent_);

  //Init command manager
  auto& cmd_mng = CmdManager::GetInstance();
  cmd_mng.Init(this);
}

void TrussApp::StartUp()
{
  
}

void TrussApp::OnRender()
{
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
  RenderMainMenuBar();

  component_manager_.Render<Workspace>();
  component_manager_.Render<LogWindow>();
 

  if (show_demo_window_) { ImGui::ShowDemoWindow(&show_demo_window_); }
}

void TrussApp::RenderMainMenuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Siema"))
      {
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
      if (ImGui::MenuItem("Show Log window"))
      {
        component_manager_.GetComponentByType<LogWindow>().lock()->Toggle();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
