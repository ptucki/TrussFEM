#include <imgui.h>
#include "workspace.h"
#include <string>
#include <iostream>


Workspace::Workspace() : BaseComponent("Workspace", "Workspace"), state_{ true }
{

}


void Workspace::OnRender()
{
  if (state_ && ImGui::Begin(GetComponentHeader().c_str(), &state_, ImGuiWindowFlags_MenuBar))
  {
    if (ImGui::Button("Add Element"))
    {
      std::cout << "state_: " << state_ << std::endl;
      //state_ = !state_;
      SetLabel("Bugatti");
    }
    ImGui::End();
  }

}
