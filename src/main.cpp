#include "application.h"
#include <iostream>

class TrussApp : public Application<TrussApp>
{
public:
  TrussApp() = default;
  ~TrussApp() = default;

  void StartUp()
  {
    std::cout << "Test" << std::endl;
  }

  void Update()
  {
    if (ImGui::BeginMainMenuBar()) //To-Do callback? member function?
    {
      ImGui::EndMainMenuBar();
    }
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    if (show_demo_window_) { ImGui::ShowDemoWindow(&show_demo_window_); }
  }

private:
  bool show_demo_window_ = true;
};

int main(int argc, char** argv)
{
  TrussApp app;
  app.Run();

  return 0;
}