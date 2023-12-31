#ifndef QUICK_COMMAND_H
#define QUICK_COMMAND_H

#include "base_command.h"

class QuickCommand : public BaseCommand
{
public:
  QuickCommand(const char* invoker, const std::function<bool(std::string&)>& callable);
protected:
  bool OnExecute(Option& current_option) override;
private:
  std::function<bool(std::string&)> callable_;
  const std::string invoker_;
};


#endif // !CLS_COMMAND_H
