#include "truss_app.h"
#include "comp/workspace.h"
#include "comp/log_window.h"

#include <iostream>

constexpr const char* workspace_id  = "Workspace";
constexpr const char* log_window_id = "LogWindow";

TrussApp::TrussApp()
  : project_{ std::make_shared<Project>() }
{

}

void TrussApp::StartUp()
{
  this->AttachComponent<Workspace>(project_);
  this->AttachComponent<LogWindow>();
}


void TrussApp::Update()
{
  Render();
}

void TrussApp::OnRender()
{
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
  RenderMainMenuBar();
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
        auto component = std::dynamic_pointer_cast<LogWindow>(FindComponentById(log_window_id));

        component->Toggle();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
