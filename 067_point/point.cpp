#include "point.h"

#include <stdio.h>
#include <stdlib.h>

#include <cmath>

Point::Point() {
  x = 0;
  y = 0;
}
void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}
double Point::distanceFrom(const Point & p) {
  return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}
