#include <config.h>
#include <math.h>
#include <vector>
#include "point.h"


point::point (double x, double y)
{
  this->x = x;
  this->y = y;
}


point::operator double () const
{
  return sqrt (x*x + y*y);
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


point&
point::operator *= (double d)
{
  x *= d;
  y *= d;
  return *this;
}


point
operator * (const point& a, double d)
{
  return point (a) *= d;
}


point
operator * (double d, const point& a)
{
  return a * d;
}


point&
point::operator /= (double d)
{
  return *this *= 1/d;
}


point
operator / (const point& a, double d)
{
  return point (a) /= d;
}


points&
points::operator << (const point& p)
{
  insert (end (), p);
  return *this;
}
