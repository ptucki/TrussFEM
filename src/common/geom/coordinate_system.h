#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

#include "point.h"
#include "angle.h"

class CoordinateSystem
{
public:
  CoordinateSystem();
  CoordinateSystem(Point3 point, std::array<Angle, 3> rotations);

  void Rotate(double x, double y, double z);
  void Rotate(std::array<Angle, 3> rotations);
  void Translate(double x, double y, double z);
  void Translate(Point3 point);
  void SetPoint(double x, double y, double z);
  void SetPoint(Point3 point);
  bool IsGlobal();
  const Point3& GetCoordinates() const&;
  Point3& GetCoordinates()&;
  Point3&& GetCoordinates()&&;

private:
  Point3 point_;
  std::array<Angle, 3> rotations_;
};


#endif // !COORDINATE_SYSTEM_H
