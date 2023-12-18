#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <string>
#include <format>
#include <memory>
#include <vector>

class BaseComponent
{
public:

  BaseComponent(std::weak_ptr<BaseComponent> parent,std::string_view label)
    : parent_{ parent }
    , label_{ label }
  {
  }

  virtual ~BaseComponent() = default;

  virtual std::string GetComponentHeader() const = 0;

  std::string GetLabel() const { return label_; }
  void SetLabel(std::string_view label) { label_ = label; }
  virtual void OnRender() = 0;

protected:

  std::weak_ptr<BaseComponent> parent_;
  std::string label_;

private:
};

template<class Derived>
class Component : public BaseComponent
{
public:

  Component(const char* id, std::weak_ptr<BaseComponent> parent, std::string_view label)
    : BaseComponent(parent, label)
  {
    if (!is_set)
    {
      this->id = id;
      is_set = true;
    }
  }

  static const std::string& GetId()
  {
    return Component<Derived>::id;
  };

  std::string GetComponentHeader() const override final
  {
    return std::format("{}##{}", label_, id);
  }

  virtual void OnRender() override = 0;

private:

  static std::string id;
  static bool is_set;
};

template<class Derived>
bool Component<Derived>::is_set = false;

template<class Derived>
std::string Component<Derived>::id = "";

#endif // !BASE_COMPONENT_H
