#include "project.h"

#include <iostream>

void Project::AddElement(Node<3> i, Node<3> j)
{
  //Check if Node exists at such a location

  //Add element if exists
  nodes_.push_back(std::make_shared<Node<3>>(i));
  nodes_.push_back(std::make_shared<Node<3>>(j));
  auto before_last = nodes_.end() - 2;
  auto last = nodes_.end() - 1;
  elements_.emplace_back(std::make_shared<Element<3>>(*before_last, *last));
}

Project::ElementList& Project::GetElementList()
{
  return elements_;
}

Element<3>& Project::GetElementAt(size_t index)
{
  return *elements_[index];
}
