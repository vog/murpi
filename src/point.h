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

};


/*
 * a vector of points
 */

class points : public vector<point>
{
public:

  points&
  add (double x, double y);

};


#endif
