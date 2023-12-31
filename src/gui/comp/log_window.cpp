#include "imgui.h"
#include <format>
#include "imgui_extension.h"
#include "command_manager.h"

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
      ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15, 0.15, 0.15, 1));
      if (ImGui::BeginChild(std::format("bbb##{}childWindow", GetId()).c_str(), first_child, ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar))
      {

        if (messages_.size() > 0 && messages_.front().empty())
        {
          messages_.pop_front();
        }
        for (auto& message : messages_)
        {
          ImGui::TextWrapped(message.c_str());
        }
      }
      ImGui::EndChild();
      ImGui::PopStyleColor();


      ImGui::SetNextItemWidth(-FLT_MIN);
      if (ImGuiEX::InputText(std::format("##{}childWindow2", GetId()).c_str(), &command_line_buffer_, "command: ", &input_state_, ImGuiInputTextFlags_EnterReturnsTrue))
      {
        //multi_line_buffer_ += "> " + command_line_buffer_ + '\n';
        messages_.emplace_back("> " + command_line_buffer_);
        if (messages_.size() > 30)
        {
          messages_.pop_front();
        }
        auto command_ptr = CmdManager::GetInstance().Request(command_line_buffer_);
        if (!command_ptr.expired())
        {
          auto cmd = command_ptr.lock();
          //if(cmd->Execute()) multi_line_buffer_ += cmd->GetResult() + '\n';
          cmd->Execute();
          messages_.emplace_back(cmd->GetResult());
        }
        else
        {
          //multi_line_buffer_ += "Unrecognized command";
          messages_.emplace_back("Unrecognized command");
        }





        ImGui::SetKeyboardFocusHere(-1);
      }


      ImGui::End();
    }
    ImGui::PopStyleVar(2);
    ImGui::PopFont();
  }

}
