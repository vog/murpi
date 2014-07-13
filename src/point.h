#ifndef __POINT_HEADER
#define __POINT_HEADER


#include <config.h>
#include <vector>


/*
 * a single point in 2D
 */

class point
{
public:

  double x, y;

  point (double x, double y);

  operator double () const;

  point
  operator - ();

  point&
  operator += (point const& p);

  friend point
  operator + (point const& a, point const& b);

  point&
  operator -= (point const& p);

  friend point
  operator - (point const& a, point const& b);

  point&
  operator *= (double d);

  friend point
  operator * (point const& a, double d);

  friend point
  operator * (double d, point const& a);

  point&
  operator /= (double d);

  friend point
  operator / (point const& a, double d);

};


/*
 * a rectangle in 2D
 */

class rect
{
private:

  double x1, y1, x2, y2;

public:

  rect (point const& p);

  rect (point const& p1, point const& p2);

  rect (double x, double y);

  rect (double x1, double y1, double x2, double y2);

  rect&
  operator = (point const& p);

  rect&
  set (point const& p1, point const& p2);

  rect&
  set (double x, double y);

  rect&
  set (double x1, double y1, double x2, double y2);

  rect&
  operator += (point const& p);

  rect&
  add (double x, double y);

  point
  p1 () const;

  point
  p2 () const;

  point
  size () const;

};


/*
 * a vector of points
 */

class points : public std::vector<point>
{
public:

  points&
  operator << (point const& p);

  rect
  getBounds () const;

  void
  setBounds (rect const& bounds, bool keep_proportion = false);

};


#endif
