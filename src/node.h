#ifndef NODE_H
#define NODE_H

#include "point.h"
#include "utilities.h"

/**
* @brief Class that represents node.
*
* @param N node number of cooridnate's dimentions
*/
template<int N = 2>
class Node : public Point<N, double>
{
public:

  /**
  * Constructs a new node
  * @brief Default constructor
  * @see template<typename T, typename ...Args> requires arithmetic<T> Node(T arg, Args... args);
  * @see Node(Point<N> p);
  */
  Node();

  /**
  * Constructs a new node
  * @brief Constructor
  * @param T - arithmetic type of first argument
  * @param Args - types of rest arguments
  * @param arg - first argument
  * @param args - rest of arguments
  * @see Node();
  * @see Node(Point<N> p);
  */
  template<typename T, typename ...Args>
    requires arithmetic<T>
  Node(T arg, Args... args);

  /**
  * Constructs a new node
  * @brief Constructor
  * @param p - point coordinates
  * @see Node();
  * @see template<typename T, typename ...Args> requires arithmetic<T> Node(T arg, Args... args);
  */
  Node(Point<N> p);

private:

};

template<int N>
inline Node<N>::Node() : Point<N>()
{

}

template<int N>
inline Node<N>::Node(Point<N> p) : Point<N>(p)
{
}

template<int N>
template<typename T, typename ...Args>
  requires arithmetic<T>
Node<N>::Node(T arg, Args ...args) : Point<N>(arg, args...)
{

}

#endif // !NODE_H
