#ifndef WORKSPACE_H
#define WORKSAPCE_H

#include <string>
#include <memory>
#include "base_component.h"
#include "project.h"

#define WORKSPACE_COLUMN_COUNT 6

class Workspace : public Component<Workspace>
{
public:
  Workspace(std::weak_ptr<BaseComponent> parent, std::weak_ptr<Project> project);

  ~Workspace() = default;

  void OnRender() override;

private:

  void Action_PrepareDataToDisplay();
  void Action_AddElement();

  void Render_ElementTable();

  std::weak_ptr<Project> project_;
  bool state_;

  std::vector<std::array<std::string, WORKSPACE_COLUMN_COUNT>> table_data_;
  bool prepare_data_;

  std::string input_text_buffer_;
  bool input_text_reset_;

GUI_STYLE:

};


#endif // !WORKSPACE_H
