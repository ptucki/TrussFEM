#ifndef PROJECT_H
#define PROJECT_H

#include <memory>
#include <vector>
#include <set>

#include "node.h"
#include "element.h"
#include "coordinate_system.h"


class Project
{
  using ElementList = std::vector<std::shared_ptr<Element<3>>>;
  using NodeList    = std::vector<std::shared_ptr<Node<3>>>;

public:

  Project();

  void AddElement(Node<3> i, Node<3> j);

  ElementList&       GetElementList() &;
  const ElementList& GetElementList() const&;
  ElementList&&      GetElementList() &&;

  NodeList&          GetNodeList() &;
  const NodeList&    GetNodeList() const&;
  NodeList&&         GetNodeList() &&;

  Element<3>&        GetElementAt(size_t index);
  Node<3>&           GetNodeAt(size_t index);

  const CoordinateSystem& GetCoordinateSystem() const;

  void SetLocalCoordinateSystem(Point3 point, std::array<Angle, 3> rotations);

private:
  NodeList nodes_;
  ElementList elements_;
  CoordinateSystem coord_sys_;
};

#endif // !PROJECT_H
