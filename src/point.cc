#include <config.h>
#include <vector>
#include "point.h"


point::point (double x, double y)
{
  this->x = x;
  this->y = y;
}


points&
points::add (double x, double y)
{
  insert (end (), point (x, y));
  return *this;
}
