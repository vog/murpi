#include <config.h>
#include <math.h>
#include "point.h"
#include "bezier.h"


/*
 * calculates the bezier curve
 */

points
Bezier2P::calc (const points& path, int steps)
{
  const uint size = path.size ();
  points bezier;

  // invalid case
  if (size < 2)
    {
      return bezier;
    }

  // special case
  if (size == 2)
    {
      calc2P (path[0], path[1],
	      path[1] - path[0], path[1] - path[0],
	      bezier, steps);
      return bezier;
    }

  // start
  calc2P (path[0], path[1],
	  path[1] - path[0], path[2] - path[0],
	  bezier, steps);

  // between
  for (uint i = 0; i + 3 < size; i++)
    {
      calc2P (path[i+1], path[i+2],
	      path[i+2] - path[i], path[i+3] - path[i+1],
	      bezier, steps);
    }

  // start
  calc2P (path[size-2], path[size-1],
	  path[size-1] - path[size-3], path[size-1] - path[size-2],
	  bezier, steps);

  // add "forgotten" last point
  bezier.insert (bezier.end(), path[size-1]);

  return bezier;
}


/*
 * calculates a quadratic bezier curve through 2 points
 */

void
QuadraticBezier::calc2P (const point& p0, const point& p1,
			 const point& d0, const point& d1,
			 points& bezier, int steps)
{
}


/*
 * calculates a cubic bezier curve through 2 points
 */

void
CubicBezier::calc2P (const point& p0, const point& p1,
		     const point& d0, const point& d1,
		     points& bezier, int steps)
{
  // norm
  double n = norm (p1 - p0);

  double n0 = norm (d0);
  point D0 = n0 == 0 ? d0 : d0 * n / n0;

  double n1 = norm (d1);
  point D1 = n1 == 0 ? d1 : d1 * n / n1;

  // calculate function parameters
  double A = +2 * p0.x +1 * D0.x -2 * p1.x +1 * D1.x;
  double B = -3 * p0.x -2 * D0.x +3 * p1.x -1 * D1.x;
  double C =           +1 * D0.x;
  double D = +1 * p0.x;

  double a = +2 * p0.y +1 * D0.y -2 * p1.y +1 * D1.y;
  double b = -3 * p0.y -2 * D0.y +3 * p1.y -1 * D1.y;
  double c =           +1 * D0.y;
  double d = +1 * p0.y;

  // calculate points
  for (double i = 0, j = 1.0/steps; i < 1.0; i += j)
    {
      bezier.add (((A * i + B) * i + C) * i + D,
		  ((a * i + b) * i + c) * i + d);
    }
}


/*
 * dummy normalizing function
 */

double
CubicBezier::norm (const point& p)
{
  return 0;
}


/*
 * simple normalizing function
 */

double
SimpleNormedCubicBezier::norm (const point& p)
{
  return sqrt ((p.x * p.x) + (p.y * p.y));
}


/*
 * abs normalizing function
 */

double
AbsNormedCubicBezier::norm (const point& p)
{
  return fabs (p.x) + fabs (p.y);
}