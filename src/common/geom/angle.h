#ifndef ANGLE_H
#define ANGLE_H

#include <cmath>

#include "point.h"
#include "utilities.h"

class Angle
{
public:
  Angle();
  Angle(double radians);


  double GetDegrees() const;
  double GetShortDegrees() const;
  double GetRadians() const;

  void SetRadians(double rad);

  template<std::size_t N>
  static Angle CreateAngle(Point<N> first, Point<N> second, Point<N> center = Point<N>());

  Angle& operator+=(double value);
  Angle& operator-=(double value);
  operator double();

private:
  double rad_;
};


template<std::size_t N>
inline Angle Angle::CreateAngle(Point<N> first, Point<N> second, Point<N> center)
{
  if (first == center || second == center) return Angle(0);

  //prepare points
  if(center != Point<N>())
  {
  ForEachCorresponingItems(first.GetValues(), center.GetValues(), [](auto& item1, auto& item2) {
    item1 -= item2;
    });

  ForEachCorresponingItems(second.GetValues(), center.GetValues(), [](auto& item1, auto& item2) {
    item1 -= item2;
    });
  }

  auto it1  = std::begin(first.GetValues());
  auto it2  = std::begin(second.GetValues());
  auto end1 = std::end(first.GetValues());
  auto end2 = std::end(first.GetValues());

  double dot_product = 0.0;
  double first_len = 0.0;
  double second_len = 0.0;

  while (it1 != end1)
  {
    dot_product += ((*it1) * (*it2));

    first_len  += pow(*it1, 2);
    second_len += pow(*it2, 2);
    it1++;
    it2++;
  }
 
  first_len  = sqrt(first_len);
  second_len = sqrt(second_len);

  return Angle(acos(dot_product / (first_len * second_len)));
}

#endif // !ANGLE_H
