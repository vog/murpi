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
 * a vector of points
 */

class points : public vector<point>
{
public:

  points&
  operator << (point const& p);

};


#endif
