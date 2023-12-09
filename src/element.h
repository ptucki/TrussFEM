#ifndef ELEMENT_H
#define ELEMENT_H

#include <memory>
#include "node.h"


template<int N = 2>
class Element
{
public:
  Element();
  Element(std::shared_ptr<Node<N>> i, std::shared_ptr<Node<N>> j);

private:
  std::weak_ptr<Node<N>> i_;
  std::weak_ptr<Node<N>> j_;
};

template<int N>
Element<N>::Element() : i_{ nullptr }, j_{ nullptr }
{

}

template<int N>
inline Element<N>::Element(std::shared_ptr<Node<N>> i, std::shared_ptr<Node<N>> j) : i_{ i }, j_{ j }
{

}

#endif // !ELEMENT_H
