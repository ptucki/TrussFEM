#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <string>
#include <format>

class BaseComponent
{
public:

  BaseComponent(std::string_view label, const char* id)
    : label_{ label }
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

protected:

private:
  const char* id_;
  std::string label_; 
};

#endif // !BASE_COMPONENT_H
