#include <imgui.h>
#include "log_window.h"


LogWindow::LogWindow()
  : BaseComponent("Log Window", "LogWindow")
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
