#include "coordinate_system.h"

CoordinateSystem::CoordinateSystem()
  : point_{ Point<3,double>{0} }
  , rotations_{ 0 }
{
}

CoordinateSystem::CoordinateSystem(Point3 point, std::array<Angle, 3> rotations)
  : point_{ point }
  , rotations_ { rotations }
{
}

void CoordinateSystem::Rotate(double x, double y, double z)
{
  rotations_[0] += x;
  rotations_[1] += y;
  rotations_[2] += z;
}

void CoordinateSystem::Rotate(std::array<Angle, 3> rotations)
{
  auto increase_rotation = std::begin(rotations);
  for (auto& axis_rotation : rotations_)
  {
    axis_rotation += *increase_rotation;
    increase_rotation++;
  }
}

void CoordinateSystem::Translate(double x, double y, double z)
{
  point_ += Point<3>(x, y, z);
}

void CoordinateSystem::Translate(Point3 point)
{
  point_ += point;
}

void CoordinateSystem::SetPoint(double x, double y, double z)
{
  point_ = Point3(x, y, z);
}

void CoordinateSystem::SetPoint(Point3 point)
{
  point_ = point;
}

bool CoordinateSystem::IsGlobal()
{
  return point_ == Point3(0,0,0);
}

const Point3& CoordinateSystem::GetCoordinates() const&
{
  return point_;
}

Point3& CoordinateSystem::GetCoordinates()&
{
  return point_;
}

Point3&& CoordinateSystem::GetCoordinates()&&
{
  return std::move(point_);
}


