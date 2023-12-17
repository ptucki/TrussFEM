#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <string>
#include <format>
#include <memory>
#include <vector>

class BaseComponent : public std::enable_shared_from_this<BaseComponent>
{
public:

  BaseComponent(std::weak_ptr<BaseComponent> parent,std::string_view label, const char* id)
    : parent_{ parent }
    , label_{ label }
    , id_{ id }
  {}

  virtual ~BaseComponent() = default;

  virtual void OnRender() = 0;
  const char* GetId() const { return id_; }
  std::string GetLabel() const { return label_; }
  void SetLabel(std::string_view label) { label_ = label; }

  std::string GetComponentHeader() const
  {
    return std::format("{}##{}", label_, id_);
  }

  template<class Component, typename... Args>
    requires std::is_base_of<BaseComponent, Component>::value
  void AttachComponent(Args&&... args)
  {
    children_.push_back(std::make_shared<Component>(weak_from_this(), std::forward<Args>(args)...));
  }

protected:

  void Render()
  {
    OnRender();
    for (auto& child : children_) child->Render();
  }

  const char* id_;
  std::string label_;
  std::weak_ptr<BaseComponent> parent_;
  std::vector<std::shared_ptr<BaseComponent>> children_;

private:
};

#endif // !BASE_COMPONENT_H
