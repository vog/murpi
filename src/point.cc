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
point::operator - ()
{
  return point (-x, -y);
}


point&
point::operator += (point const& p)
{
  x += p.x;
  y += p.y;
  return *this;
}


point
operator + (point const& a, point const& b)
{
  return point (a) += b;
}


point&
point::operator -= (point const& p)
{
  return *this += -(point)p;
}


point
operator - (point const& a, point const& b)
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
operator * (point const& a, double d)
{
  return point (a) *= d;
}


point
operator * (double d, point const& a)
{
  return a * d;
}


point&
point::operator /= (double d)
{
  return *this *= 1/d;
}


point
operator / (point const& a, double d)
{
  return point (a) /= d;
}


points&
points::operator << (point const& p)
{
  insert (end (), p);
  return *this;
}
