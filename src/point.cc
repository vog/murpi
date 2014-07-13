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


rect::rect (point const& p)
{
  rect (p.x, p.y);
}


rect::rect (point const& p1, point const& p2)
{
  rect (p1.x, p1.y, p2.x, p2.y);
}


rect::rect (double x, double y)
{
  set (x, y);
}


rect::rect (double x1, double y1, double x2, double y2)
{
  set (x1, y1, x2, y2);
}


rect&
rect::operator = (point const& p)
{
  return set (p.x, p.y);
}


rect&
rect::set (point const& p1, point const& p2)
{
  return set (p1.x, p1.y, p2.x, p2.y);
}


rect&
rect::set (double x, double y)
{
  x1 = x2 = x;
  y1 = y2 = y;
  return *this;
}


rect&
rect::set (double x1, double y1, double x2, double y2)
{
  set (x1, y1);
  return add (x2, y2);
}


rect&
rect::operator += (point const& p)
{
  return add (p.x, p.y);
}


rect&
rect::add (double x, double y)
{
  if (x < x1) x1 = x;
  if (x > x2) x2 = x;
  if (y < y1) y1 = y;
  if (y > y2) y2 = y;
  return *this;
}


point
rect::p1 () const
{
  return point (x1, y1);
}


point
rect::p2 () const
{
  return point (x2, y2);
}


point
rect::size () const
{
  return point (x2 - x1, y2 - y1);
}


points&
points::operator << (point const& p)
{
  insert (end (), p);
  return *this;
}


rect
points::getBounds () const
{
  const_iterator i = begin ();

  if (i != end ())
    {
      rect r = *i;
      for (i++; i != end (); i++)
	r += *i;
      return r;
    }

  return rect (0,0);
}


void
points::setBounds (rect const& bounds, bool keep_proportion)
{
  rect r = getBounds ();
  point s = r.size ();
  if (s.x == 0 || s.y == 0) return;

  double fx = bounds.size ().x / s.x;
  double fy = bounds.size ().y / s.y;
  if (keep_proportion) fx = fy = std::min (fx, fy);
  double ox = bounds.p1 ().x - r.p1 ().x * fx;
  double oy = bounds.p1 ().y - r.p1 ().y * fy;

  for (iterator i = begin (); i != end (); i++)
    {
      (*i).x = ox + (*i).x * fx;
      (*i).y = oy + (*i).y * fy;
    }
}
