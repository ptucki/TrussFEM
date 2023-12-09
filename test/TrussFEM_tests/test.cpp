#include "pch.h"

#include <iostream>
#include "point.h"

TEST(TestCaseName, Point_GetX)
{
  Point<3> a{ 1.2, 2.3, 4.3 };
  EXPECT_EQ(a.GetX(), 1.2);
}

TEST(TestCaseName, Point_GetY)
{
  Point<3> a{ 1.2, 2.3, 4.3 };
  EXPECT_EQ(a.GetY(), 2.3);
}

TEST(TestCaseName, Point_GetZ)
{
  Point<3> a{ 1.2, 2.3, 4.3 };
  EXPECT_EQ(a.GetZ(), 4.3);
}

TEST(TestCaseName, Point_get)
{
  Point<3> a{ 1.2, 2.3, 4.3 };
  EXPECT_EQ(a.get<0>(), 1.2);
  EXPECT_EQ(a.get<1>(), 2.3);
  EXPECT_EQ(a.get<2>(), 4.3);
}