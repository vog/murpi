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

  friend point
  operator - (const point& p);

  point&
  operator += (const point& p);

  friend point
  operator + (const point& a, const point& b);

  point&
  operator -= (const point& p);

  friend point
  operator - (const point& a, const point& b);

  point&
  operator *= (double d);

  friend point
  operator * (const point& a, double d);

  friend point
  operator * (double d, const point& a);

  point&
  operator /= (double d);

  friend point
  operator / (const point& a, double d);

};


/*
 * a vector of points
 */

class points : public vector<point>
{
public:

  points&
  operator << (const point& p);

};


#endif
