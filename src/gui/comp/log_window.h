#ifndef LOG_WINDOW_H
#define LOG_WINDOW_H

#include "base_component.h"

class LogWindow : public BaseComponent
{
public:
  LogWindow(std::weak_ptr<BaseComponent> parent);
  ~LogWindow() = default;

  void OnRender() override;

  void Toggle() { open_ = !open_; }
private:
  bool open_;
};


#endif // !LOG_WINDOW_H
