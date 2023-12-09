#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "point.h"
#include "node.h"
#include "element.h"
#include "arithmetic.h"


#ifndef LIB_BUILD

class Solution
{
public:

  void AddElement(Node<3> i, Node<3> j)
  {
    //Check if Node exists at such a location

    //Add element if exists
    nodes_.emplace_back(std::make_shared<Node<3>>(i));
    nodes_.emplace_back(std::make_shared<Node<3>>(j));
    auto before_last = nodes_.end() - 2;
    auto last = nodes_.end() - 1;
    elements_.emplace_back(std::make_shared<Element<3>>(*before_last, *last));
  }

private:
  std::vector<std::shared_ptr<Node<3>>> nodes_;
  std::vector<std::shared_ptr<Element<3>>> elements_;
};

int main(int argc, char** argv)
{
  Solution sol;

  Point<3, double> p1(1.0, 2.0, 3.00000000000004);
  Point<3, int> p2(1, 2, 3);
  auto bbb = static_cast<std::array<int, 3>>(p2);
  auto ccc = static_cast<Point<3, double>>(p2);

  std::cout << (p1 == static_cast<Point<3, double>>(p2)) << std::endl;

  p1.Print();
  p2.Print();
  //p1 == static_cast<double>(p2);


  return 0;
}

#endif
