#include "point.h"
class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(Point p, double d) : center(p), radius(d) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
