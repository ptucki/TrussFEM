#ifndef WORKSPACE_H
#define WORKSAPCE_H

#include <string>
#include <memory>
#include "base_component.h"
#include "imgui_extension.h"
#include "project.h"

class Workspace : public Component<Workspace>
{
public:
  Workspace(std::weak_ptr<BaseComponent> parent, std::weak_ptr<Project> project);

  ~Workspace() = default;

  void OnRender() override;

private:

  enum class ComboBoxOption
  {
    ElementTable = 0,
    NodeTable
  };

  void Action_PrepareDataToDisplay();
  void Action_AddElement();
  bool Action_OnElementTableInput(TableDataPack& data_pack);

  void Render_ComboBox();

  std::weak_ptr<Project> project_;
  bool state_;

  //Element Table
  std::vector<std::array<std::string, 6>> element_table_data_;
  bool prepare_data_;

  //Node Table
  std::vector<std::array<std::string, 3>> node_table_data_;

  std::string input_text_buffer_;
  bool input_text_reset_;

  //Combobox
  ComboBoxOption cbox_current_option_;
  const char* cbox_preview_value_;

GUI_STYLE:

};


#endif // !WORKSPACE_H
