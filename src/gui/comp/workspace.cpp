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
  , cbox_current_option_{ static_cast<ComboBoxOption>(0) }
{
  Action_PrepareDataToDisplay();

  input_text_buffer_.reserve(50);
}


void Workspace::OnRender()
{
  if (state_ && ImGui::Begin(GetComponentHeader().c_str(), &state_))
  {
    auto project = project_.lock();

    if (ImGui::BeginChild(PrepareSubItemHeader("", "child1").c_str(), ImVec2(ImGui::GetContentRegionAvail().x * 0.667f, 0.0f), ImGuiChildFlags_Border))
    {

      Render_ComboBox();

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

      switch (cbox_current_option_)
      {

      case Workspace::ComboBoxOption::ElementTable:
      {
        std::array<const char*, 6> element_column_name = { "X1", "Y1", "Z1", "X2", "Y2", "Z2" };

        ImGuiEX::EditableTable(PrepareSubItemHeader(
          "",
          "ElementTable").c_str(),
          element_column_name,
          element_table_data_,
          &Workspace::Action_OnElementTableInput,
          this,
          project.get(),
          ImGuiTableFlags_Borders);
        break;
      }

      case Workspace::ComboBoxOption::NodeTable:
      {
        std::array<const char*, 3> node_column_name = { "X", "Y", "Z" };

        ImGuiEX::EditableTable(PrepareSubItemHeader(
          "",
          "NodeTable").c_str(),
          node_column_name,
          node_table_data_,
          &Workspace::Action_OnNodeTableInput,
          this,
          project.get(),
          ImGuiTableFlags_Borders);
        break;
      }

      default:
        break;
      }
    }
    ImGui::EndChild();

    ImGui::SameLine();

    if (ImGui::BeginChild(PrepareSubItemHeader("", "child2").c_str(), ImVec2(0, 0), ImGuiChildFlags_Border))
    {
      auto coord_sys = project->GetCoordinateSystem();
      auto ucs_point = coord_sys.GetCoordinates();

      if (coord_sys.IsGlobal())
      {
        ImGui::Text("Global coordinate system");
        ImGui::TextDisabled(std::format("X: {:.{}f}", ucs_point.GetX(), 3).c_str());
        ImGui::TextDisabled(std::format("Y: {:.{}f}", ucs_point.GetY(), 3).c_str());
        ImGui::TextDisabled(std::format("Z: {:.{}f}", ucs_point.GetZ(), 3).c_str());
      }
      else
      {
        ImGui::Text("Local coordinate system");
        ImGui::Text(std::format("X: {:.{}f}", ucs_point.GetX(), 3).c_str());
        ImGui::Text(std::format("Y: {:.{}f}", ucs_point.GetY(), 3).c_str());
        ImGui::Text(std::format("Z: {:.{}f}", ucs_point.GetZ(), 3).c_str());
      }
    }

    ImGui::EndChild();

    ImGui::End();
  }

}

void Workspace::Action_PrepareDataToDisplay()
{
  auto project          { project_.lock() };
  size_t current_row    { 0 };
  size_t current_column { 0 };

  element_table_data_.clear();
  node_table_data_.clear();

  element_table_data_.resize(project->GetElementList().size());
  node_table_data_.resize(project->GetNodeList().size());

  auto coord_sys = project->GetCoordinateSystem();
  //Prepare element table
  for (auto& element : project->GetElementList())
  {
    auto& node_i{ element->GetNodeI() };
    auto& node_j{ element->GetNodeJ() };

    auto node_i_local = SumArrays(node_i.GetValues(), static_cast<std::array<double,3>>(coord_sys.GetCoordinates()));
    auto node_j_local = SumArrays(node_j.GetValues(), static_cast<std::array<double, 3>>(coord_sys.GetCoordinates()));

    auto element_data{ ConcatArrays(node_i_local, node_j_local) };
    auto& row{ element_table_data_[current_row++] };

    for (auto& cell : row)
    {
      auto temp{ std::format("{:.{}f}",element_data[current_column++], 3) };
      cell = std::move(temp);
    }
    current_column = 0;
  }

  current_row = 0;
  current_column = 0;

  //Prepare node table
  for (auto& node : project->GetNodeList())
  {
    auto& row{ node_table_data_[current_row++] };

    for (auto& cell : row)
    {
      auto& values{ node->GetValues() };

      auto temp{ std::format("{:.{}f}", values[current_column++], 3) };
      cell = std::move(temp);
    }

    current_column = 0;
  }
}

void Workspace::Action_AddElement()
{
  if (auto project = project_.lock(); 0 != strcmp(input_text_buffer_.c_str(), input_label))
  {
    if (auto coordinates{ SplitString(input_text_buffer_, ',') }; coordinates.size() == 6)
    {
      auto f_cords = ConvertStringListToFloats(coordinates);
      Node<3> i{f_cords[0], f_cords[1], f_cords[2]};
      Node<3> j{f_cords[3], f_cords[4], f_cords[5]};
      project->AddElement(i, j);

      auto cords_arr{ ConcatArrays(i.GetValues(), j.GetValues()) };

      element_table_data_.push_back(StringifyArrayItems(cords_arr, "{:.{}f}", 3));

      if (auto& project_node_list{ project->GetNodeList() }; project_node_list.size() != node_table_data_.size())
      {
        auto difference{ project_node_list.size() - node_table_data_.size() };
        auto new_node{ std::begin(project_node_list) + project_node_list.size() - difference };
        
        while (new_node != std::end(project_node_list))
        {
          node_table_data_.push_back(StringifyArrayItems(new_node->get()->GetValues(),"{:.{}f}", 3));
          new_node++;
        }
      }
    }

    input_text_reset_ = true;
    input_text_buffer_ = "";
    ImGui::SetItemDefaultFocus();
  }
}

bool Workspace::Action_OnElementTableInput(TableDataPack& data_pack)
{
  auto project{ static_cast<Project*>(data_pack.user_data) };
  auto current_row{ data_pack.row };
  auto current_column{ data_pack.column };
  auto& element{ project->GetElementAt(current_row) };
  auto index{ static_cast<int>(current_column) / element.DimensionCount() };
  auto coordinate{ static_cast<int>(current_column) % element.DimensionCount() };

  std::array<Node<3>*, 2> nodes{ &element.GetNodeI(), &element.GetNodeJ() };

  nodes[index]->SetValueAt(static_cast<int>(coordinate), std::stod(data_pack.item.c_str()));

  Action_PrepareDataToDisplay();

  return true;
}

bool Workspace::Action_OnNodeTableInput(TableDataPack& data_pack)
{
  auto project{ static_cast<Project*>(data_pack.user_data) };
  auto current_row{ data_pack.row };
  auto current_column{ data_pack.column };
  auto& node{ project->GetNodeAt(current_row) };
  auto coordinate{ static_cast<int>(current_column) % node.DimensionCount() };

  node.SetValueAt(static_cast<int>(current_column), std::stod(data_pack.item.c_str()));

  Action_PrepareDataToDisplay();

  return true;
}

void Workspace::Render_ComboBox()
{
  std::array<const char*,2> items = { "Elements", "Nodes" };
  auto current_option = ToUnderlying(cbox_current_option_);
  const char* combo_preview_value = items[current_option];

  if (ImGui::BeginCombo(PrepareSubItemHeader("","Combobox").c_str(), combo_preview_value, ImGuiComboFlags_HeightSmall))
  {
    for (int n = 0; n < items.size(); n++)
    {
      const bool is_selected = (current_option == n);
      if (ImGui::Selectable(items[n], is_selected))
        cbox_current_option_ = static_cast<ComboBoxOption>(n);

      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }

}
