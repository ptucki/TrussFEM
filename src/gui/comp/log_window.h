#ifndef LOG_WINDOW_H
#define LOG_WINDOW_H

#include <list>
#include "base_component.h"

class LogWindow : public Component<LogWindow>
{
public:
  LogWindow(std::weak_ptr<BaseComponent> parent);
  ~LogWindow() = default;

  void OnRender() override;

  void Toggle() { opened_ = !opened_; }
  std::list<std::string>& GetResource_ConsoleLogBuffer()& { return messages_; }

COMP_STATE:
  std::string id_messages_;

  bool opened_;

  std::vector<std::string> values_; //To be deleted when logger

  std::string command_line_buffer_;
  //std::string multi_line_buffer_;
  std::list<std::string> messages_;
  bool input_state_;


GUI_STYLE:
  float input_height;
};


#endif // !LOG_WINDOW_H
