#include <imgui.h>
#include "log_window.h"


LogWindow::LogWindow(std::weak_ptr<BaseComponent> parent)
  : Component<LogWindow>("LogWindow", parent, "Log Window")
  , open_{ true }
{

}

void LogWindow::OnRender()
{
  if (open_ && ImGui::Begin(GetComponentHeader().c_str(), &open_))
  {
    ImGui::End();
  }
}
