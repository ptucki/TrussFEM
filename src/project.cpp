#include "project.h"

#include <memory>
#include <iostream>

void Project::AddElement(Node<3> i, Node<3> j)
{
  //Check if Node exists at such a location
  std::shared_ptr<Node<3>> i_node = std::make_shared<Node<3>>(std::move(i));
  std::shared_ptr<Node<3>> j_node = std::make_shared<Node<3>>(std::move(j));
  auto end = nodes_.end();

  bool i_node_found = false;
  bool j_node_found = false;

  for (auto it = std::begin(nodes_); it != std::end(nodes_); ++it)
  {
    if (**it == i)
    {
      i_node_found = true;
      i_node = *it;
    }
    if (**it == j)
    {
      j_node_found = true;
      i_node = *it;
    }
  }

  if (!i_node_found) nodes_.push_back(std::move(i_node));
  if (!j_node_found) nodes_.push_back(std::move(j_node));

  elements_.emplace_back(std::make_shared<Element<3>>(nodes_[nodes_.size() - 2], nodes_[nodes_.size() - 1]));
}

Project::ElementList& Project::GetElementList() &
{
  return elements_;
}

Project::ElementList&& Project::GetElementList() &&
{
  return std::move(elements_);
}

const Project::ElementList& Project::GetElementList() const&
{
  return elements_;
}

Project::NodeList& Project::GetNodeList() &
{
  return nodes_;
}

Project::NodeList&& Project::GetNodeList() &&
{
  return std::move(nodes_);
}

const Project::NodeList& Project::GetNodeList() const&
{
  return nodes_;
}


Element<3>& Project::GetElementAt(size_t index)
{
  return *elements_[index];
}
