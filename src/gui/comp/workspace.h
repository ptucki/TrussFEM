#ifndef WORKSPACE_H
#define WORKSAPCE_H

#include <string>
#include "base_component.h"


class Workspace : public BaseComponent
{
public:
  Workspace();

  ~Workspace() = default;

  void OnRender() override;

private:
  bool state_;
};


#endif // !WORKSPACE_H
