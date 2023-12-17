#include <imgui.h>
#include "workspace.h"
#include <string>
#include <array>
#include <iostream>
#include <format>


Workspace::Workspace(std::weak_ptr<BaseComponent> parent, std::weak_ptr<Project> project)
  : BaseComponent(parent, "Workspace", "Workspace")
  , state_{ true }
  , project_{ project }
  , prepare_data_{ false }
{
  PrepareDataToDisplay();
}


void Workspace::OnRender()
{
  if (state_ && ImGui::Begin(GetComponentHeader().c_str(), &state_, ImGuiWindowFlags_MenuBar))
  {
    auto project = project_.lock();

    if (ImGui::Button("Add Element"))
    {
      project->AddElement({1,2,3},{3,4,5});
      prepare_data_ = true;
    }

    if (ImGui::BeginTable("Element Table", WORKSPACE_COLUMN_COUNT, ImGuiTableFlags_Borders))
    {
      std::array<const char*, WORKSPACE_COLUMN_COUNT> column_name = { "X1", "Y1", "Z1", "X2", "Y2", "Z2" };
      
      for(auto column : column_name) ImGui::TableSetupColumn(column);
      ImGui::TableHeadersRow();

      if (prepare_data_) {
        PrepareDataToDisplay();
        prepare_data_ = !prepare_data_;
      }

      size_t current_row{ 0 };
      size_t current_column{ 0 };

      for (auto& row : table_data_)
      {
        ImGui::TableNextRow();

        for (auto& cell : row)
        {
          ImGui::TableSetColumnIndex(static_cast<int>(current_column));
          ImGui::SetNextItemWidth(-FLT_MIN);

          auto input_text_label = std::format("##workspace{}_{}", current_row, current_column);
          if (ImGui::InputText(input_text_label.c_str(), cell.data(), cell.capacity(), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsDecimal))
          {
            auto& element   { project->GetElementAt(current_row) };
            auto index      { static_cast<int>(current_column) / element.DimensionCount() };
            auto coordinate { current_column % element.DimensionCount() };

            std::array<Node<3>*, 2> nodes{ &element.GetNodeI(), &element.GetNodeJ() };

            nodes[index]->SetValueAt(static_cast<int>(coordinate), std::stod(table_data_[current_row][current_column].c_str()));

            
            prepare_data_ = true; //RefreshCell();
            break;
          }
          current_column++;
        }
        current_column = 0;
        current_row++;
      }

      ImGui::EndTable();
    }

    ImGui::End();
  }

}

void Workspace::PrepareDataToDisplay()
{
  auto project          { project_.lock() };
  size_t current_row    { 0 };
  size_t current_column { 0 };

  table_data_.resize(project->GetElementList().size());

  for (auto& element : project->GetElementList())
  {
    auto& node_i = element->GetNodeI();
    auto& node_j = element->GetNodeJ();
    auto element_data = ConcatArrays(node_i.GetValues(), node_j.GetValues());
    auto& row = table_data_[current_row++];

    for (auto& cell : row)
    {
      auto temp = std::format("{:.{}f}",element_data[current_column++],3);
      cell = std::move(temp);
    }
    current_column = 0;
  }
}
