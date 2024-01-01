#include <numbers>

#include "angle.h"

Angle::Angle() : rad_{ 0.0 }
{
}

Angle::Angle(double radians) : rad_{ radians }
{
}

Angle::operator double()
{
  return rad_;
}

double Angle::GetDegrees() const
{
  return rad_ * (180 / std::numbers::pi_v<double>);
}

double Angle::GetShortDegrees() const
{
  return std::fmod(rad_ * (180 / std::numbers::pi_v<double>), 360.0);
}

double Angle::GetRadians() const
{
  return rad_;
}

void Angle::SetRadians(double rad)
{
  rad_ = rad;
}

Angle& Angle::operator+=(double value)
{
  rad_ += value;
  return *this;
}

Angle& Angle::operator-=(double value)
{
  rad_ -= value;
  return *this;
}
