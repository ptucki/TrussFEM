#include "imgui.h"
#include <format>
#include "imgui_extension.h"

#include "log_window.h"


LogWindow::LogWindow(std::weak_ptr<BaseComponent> parent)
  : Component<LogWindow>("LogWindow", parent, "Log Window")
  , id_messages_{ PrepareSubItemHeader("", "childWindow" ) }
  , opened_{ true }
  , command_line_buffer_{ "" }
  , input_state_{ true }
  , input_height{ 2 * ImGui::GetStyle().FramePadding.y + ImGui::GetFontSize() + 2 * ImGui::GetStyle().ItemSpacing.y }
{
  command_line_buffer_.reserve(50);

}

void LogWindow::OnRender()
{

  if (opened_)
  {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    if (ImGui::Begin(GetComponentHeader().c_str(), &opened_))
    {

      ImVec2 first_child = ImVec2(0, ImGui::GetContentRegionAvail().y - (2 * ImGui::GetStyle().FramePadding.y + ImGui::GetFontSize()));
      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(30.0f, 30.0f));
      if (ImGui::BeginChild(std::format("bbb##{}childWindow", GetId()).c_str(), first_child, ImGuiChildFlags_Border))
      {
      
      }
      ImGui::EndChild();
      ImGui::PopStyleVar();


      ImGui::SetNextItemWidth(-FLT_MIN);
      if (ImGuiEX::InputText(std::format("##{}childWindow2", GetId()).c_str(), &command_line_buffer_, "command: ", &input_state_, ImGuiInputTextFlags_EnterReturnsTrue))
      {
        values_.emplace_back(std::move(command_line_buffer_));
        ImGui::SetKeyboardFocusHere(-1);
      }


      ImGui::End();
    }
    ImGui::PopStyleVar(2);
    ImGui::PopFont();
  }

}
