#include <config.h>
#include <vector>
#include "point.h"


point::point (double x, double y)
{
  this->x = x;
  this->y = y;
}


point
operator - (const point& p)
{
  return point (-p.x, -p.y);
}


point&
point::operator += (const point& p)
{
  x += p.x;
  y += p.y;
  return *this;
}


point
operator + (const point& a, const point& b)
{
  return point (a) += b;
}


point&
point::operator -= (const point& p)
{
  return *this += -p;
}


point
operator - (const point& a, const point& b)
{
  return point (a) -= b;
}


points&
points::add (double x, double y)
{
  insert (end (), point (x, y));
  return *this;
}
