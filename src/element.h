#ifndef ELEMENT_H
#define ELEMENT_H

#include <memory>
#include <utility>
#include "node.h"


template<int N = 2>
class Element
{
public:
  Element();
  Element(std::shared_ptr<Node<N>> i, std::shared_ptr<Node<N>> j);

  const Node<N>& GetNodeI() const&;
  Node<N>& GetNodeI() &;
  Node<N>&& GetNodeI() &&;

  const Node<N>& GetNodeJ() const&;
  Node<N>& GetNodeJ() &;
  Node<N>&& GetNodeJ()&&;
  const std::pair<std::weak_ptr<Node<N>>, std::weak_ptr<Node<N>>>& GetNodes() const;
  static constexpr int DimensionCount() noexcept;

private:
  std::pair<std::weak_ptr<Node<3>>, std::weak_ptr<Node<3>>> nodes_;
};

template<int N>
Element<N>::Element() : nodes_{ nullptr, nullptr }
{

}

template<int N>
inline Element<N>::Element(std::shared_ptr<Node<N>> i, std::shared_ptr<Node<N>> j) : nodes_{ i, j }
{

}

template<int N>
const Node<N>& Element<N>::GetNodeI() const&
{
  return *(nodes_.first.lock());
}

template<int N>
Node<N>& Element<N>::GetNodeI()&
{
  return *(nodes_.first.lock());
}

template<int N>
Node<N>&& Element<N>::GetNodeI()&&
{
  return std::move(*(nodes_.first.lock()));
}

template<int N>
const Node<N>& Element<N>::GetNodeJ() const&
{
  return *(nodes_.second.lock());
}

template<int N>
Node<N>& Element<N>::GetNodeJ() &
{
  return *(nodes_.second.lock());
}

template<int N>
Node<N>&& Element<N>::GetNodeJ() &&
{
  return std::move(*(nodes_.second.lock()));
}

template<int N>
const std::pair<std::weak_ptr<Node<N>>, std::weak_ptr<Node<N>>>& Element<N>::GetNodes() const
{
  return nodes_;
}

template<int N>
inline constexpr int Element<N>::DimensionCount() noexcept
{
  return N;
}

#endif // !ELEMENT_H
