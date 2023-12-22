#include "imgui.h"
#include "imgui_extension.h"
#include "utilities.h"
#include <string>
#include <array>
#include <iostream>
#include <format>

#include "workspace.h"

constexpr const char* input_label = "Write coordinates ex. 0, 0, 0, 0, 0, 0 and press [Enter] to add new element.";

Workspace::Workspace(std::weak_ptr<BaseComponent> parent, std::weak_ptr<Project> project)
  : Component<Workspace>("Workspace", parent, "Workspace")
  , state_{ true }
  , project_{ project }
  , prepare_data_{ false }
  , input_text_buffer_{""}
  , input_text_reset_{ true }
{
  Action_PrepareDataToDisplay();

  input_text_buffer_.reserve(50);
}


void Workspace::OnRender()
{
  if (state_ && ImGui::Begin(GetComponentHeader().c_str(), &state_))
  {
    auto project = project_.lock();

    if (ImGui::Button("Add Element")) Action_AddElement();

    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::SameLine();

    auto input_text_flags = 
      ImGuiInputTextFlags_EnterReturnsTrue;
    auto input = 
      ImGuiEX::InputText(
        PrepareSubItemHeader("", "InputAddElement").c_str(),
        &input_text_buffer_,
        input_label,
        &input_text_reset_,
        input_text_flags);

    if (input) Action_AddElement();

    Render_ElementTable();

    ImGui::End();
  }

}



void Workspace::Action_PrepareDataToDisplay()
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

void Workspace::Action_AddElement()
{
  auto project = project_.lock();

  if (0 != strcmp(input_text_buffer_.c_str(), input_label))
  {
    auto coordinates = SplitString(input_text_buffer_, ',');

    if (coordinates.size() == 6)
    {
      auto f_cords = ConvertStringListToFloats(coordinates);
      Node<3> i{f_cords[0], f_cords[1], f_cords[2]};
      Node<3> j{f_cords[3], f_cords[4], f_cords[5]};
      project->AddElement(i, j);

      prepare_data_ = true;
      
    }
    input_text_reset_ = true;
    input_text_buffer_ = "";
    ImGui::SetItemDefaultFocus();
  }
}

void Workspace::Render_ElementTable()
{
  auto project = project_.lock();

  if (ImGui::BeginTable("Element Table", WORKSPACE_COLUMN_COUNT, ImGuiTableFlags_Borders))
  {
    std::array<const char*, WORKSPACE_COLUMN_COUNT> column_name = { "X1", "Y1", "Z1", "X2", "Y2", "Z2" };

    for (auto column : column_name) ImGui::TableSetupColumn(column);
    ImGui::TableHeadersRow();

    if (prepare_data_) {
      Action_PrepareDataToDisplay();
      prepare_data_ = !prepare_data_;
    }

    size_t current_row{ 0 };
    size_t current_column{ 0 };

    for (auto& row : table_data_)
    {
      ImGui::TableNextRow();

      for (auto& cell : row)
      {
        auto input_text_label = std::format("##{}{}_{}", GetId(), current_row, current_column);
        
        ImGui::TableSetColumnIndex(static_cast<int>(current_column));

        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.3f, 0.3f, 0.3f, 0.0f));
        if (ImGui::InputText(input_text_label.c_str(), cell.data(), cell.capacity(), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsDecimal))
        {
          auto& element{ project->GetElementAt(current_row) };
          auto index{ static_cast<int>(current_column) / element.DimensionCount() };
          auto coordinate{ current_column % element.DimensionCount() };

          std::array<Node<3>*, 2> nodes{ &element.GetNodeI(), & element.GetNodeJ() };

          nodes[index]->SetValueAt(static_cast<int>(coordinate), std::stod(table_data_[current_row][current_column].c_str()));


          prepare_data_ = true; //RefreshCell();
          ImGui::PopStyleColor();
          break;
        }
        ImGui::PopStyleColor();
        current_column++;
      }
      current_column = 0;
      current_row++;

    }
    ImGui::EndTable();
  }
}