#ifndef NODE_H
#define NODE_H

#include "point.h"
#include "utilities.h"

template<int N = 2>
class Node : public Point<N>
{
public:

  Node();

  template<typename T, typename ...Args>
    requires arithmetic<T>
  Node(T arg, Args... args);

private:

};

template<int N>
inline Node<N>::Node() : Point<N>()
{

}

template<int N>
template<typename T, typename ...Args>
  requires arithmetic<T>
Node<N>::Node(T arg, Args ...args) : Point<N>(arg, args...)
{

}

#endif // !NODE_H
