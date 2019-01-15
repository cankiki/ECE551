#include "circle.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  Point * p1 = new Point(center);
  double d = p1->distanceFrom(otherCircle.center);
  double a =
      acos((d * d + radius * radius - otherCircle.radius * otherCircle.radius) / (2 * d * radius));
  double b = acos((d * d + otherCircle.radius * otherCircle.radius - radius * radius) /
                  (2 * d * otherCircle.radius));
  if (d >= radius + otherCircle.radius) {
    return 0;
  }
  else if (d <= abs(radius - otherCircle.radius)) {
    return acos(-1.0) * std::min(radius * radius, otherCircle.radius * otherCircle.radius);
  }
  return radius * radius * a + otherCircle.radius * otherCircle.radius * b - sin(a) * radius * d;
}
