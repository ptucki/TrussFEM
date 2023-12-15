#ifndef LOG_WINDOW_H
#define LOG_WINDOW_H

#include "base_component.h"

class LogWindow : public BaseComponent
{
public:
  LogWindow();
  ~LogWindow() = default;

  void OnRender() override;

  void Toggle() { open_ = !open_; }
private:
  bool open_;
};


#endif // !LOG_WINDOW_H
