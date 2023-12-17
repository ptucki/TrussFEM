#ifndef TRUSS_APP_H
#define TRUSS_APP_H

#include <vector>
#include <memory>
#include "application.h"
#include "base_component.h"
#include "project.h"

enum class CompId : unsigned int
{
  Undefined = 0
};

class TrussApp : public Application<TrussApp>
{
  using ComponentList = std::vector<std::shared_ptr<BaseComponent>>;
public:

  TrussApp();
  ~TrussApp() = default;

  void StartUp();
  void Update();
  void OnRender() override;
  template<class Component,typename... Args>
    requires std::is_base_of<BaseComponent, Component>::value
  void AddNewComponent(Args&&... args)
  {
    components_.push_back(std::make_shared<Component>(std::forward<Args>(args)...));
  }

  std::shared_ptr<BaseComponent> FindComponentById(const char* id)
  {
    auto item = std::find_if(std::begin(components_), std::end(components_), [id](auto item) {
      return item->GetId() == id;
      });

    return item != components_.end() ? *item : nullptr;
  }

private:

  void RenderMainMenuBar();

  // App state
  bool show_demo_window_ = true;
  ComponentList components_;
  ComponentList map_;


  // Solution
  std::shared_ptr<Project> project_;

};

#endif // !TRUSS_APP_H
