#ifndef TRUSS_APP_H
#define TRUSS_APP_H


#include <memory>
#include <utility>
#include <string>
#include "application.h"
#include "project.h"



class TrussApp : public Application<TrussApp>
{
public:

  TrussApp();
  ~TrussApp() = default;

  void StartUp();
  void OnRender();

  std::shared_ptr<Project> GetProject() const { return project_; }

private:

  void RenderMainMenuBar();

  // App state
  bool show_demo_window_ = true;

  // Solution
  std::shared_ptr<Project> project_;
};



#endif // !TRUSS_APP_H
