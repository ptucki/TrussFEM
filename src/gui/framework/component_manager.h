#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include <string>
#include <memory>
#include <utility>
#include "base_component.h"

class ComponentManager
{
public:
  using ComponentMap = std::unordered_map<std::string, std::shared_ptr<BaseComponent>> ;

  ComponentManager() = default;

  template<class Component, typename... Args>
    requires std::is_base_of<BaseComponent, Component>::value
  void AttachComponent(std::weak_ptr<BaseComponent> parent, Args&&... args)
  {
    components_.insert(
      std::make_pair(Component::GetId(),
      std::make_shared<Component>(parent, std::forward<Args>(args)...))
    );
  }

  template<class Component>
  std::weak_ptr<Component> GetComponentByType()
  {
    return std::static_pointer_cast<Component>(
      components_[Component::GetId()]
    );
  }

  std::weak_ptr<BaseComponent> GetComponentById(const std::string& id)
  {
    return components_[id];
  }

  template<class Component>
  void Render()
  {
    GetComponentById(Component::GetId()).lock()->OnRender();
  }

private:
  ComponentMap components_;
};

#endif // !COMPONENT_MANAGER_H
