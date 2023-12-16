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
  components_.emplace_back(std::make_shared<Workspace>(project_));
  components_.emplace_back(std::make_shared<LogWindow>());
}


void TrussApp::Update()
{
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
  RenderMainMenuBar();

  for (auto component : components_) component->OnRender();

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
