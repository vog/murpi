#ifndef __BEZIER_HEADER
#define __BEZIER_HEADER


#include <config.h>
#include "point.h"


/*
 * general bezier curves
 */

class Bezier
{
public:

  virtual
  ~Bezier () {};

  // calculates the bezier curve
  virtual points
  calc (const points& path, int steps) = 0;

};


/*
 * bezier curves which are drawn extra for each pair of points
 */

class Bezier2P : public Bezier
{
public:

  // calculates the bezier curve
  virtual points
  calc (const points& path, int steps);

protected:

  // calculates the bezier curve through 2 points
  virtual void
  calc2P (const point& p0, const point& p1,
	  const point& d0, const point& d1,
	  points& bezier, int steps) = 0;

};


/*
 * quadratic bezier curves
 */

class QuadraticBezier : public Bezier2P
{
protected:

  // calculates a quadratic bezier curve through 2 points
  virtual void
  calc2P (const point& p0, const point& p1,
	  const point& d0, const point& d1,
	  points& bezier, int steps);

};


/*
 * cubic bezier curves
 */

class CubicBezier : public Bezier2P
{
protected:

  // calculates a cubic bezier curve through 2 points
  virtual void
  calc2P (const point& p0, const point& p1,
	  const point& d0, const point& d1,
	  points& bezier, int steps);

  // normalizing function
  virtual double
  norm (const point& p);

};


/*
 * simple normed cubic bezier curves
 */

class SimpleNormedCubicBezier : public CubicBezier
{
protected:

  // normalizing function
  virtual double
  norm (const point& p);

};


/*
 * cubic bezier curves normed using the abs() function
 */

class AbsNormedCubicBezier : public CubicBezier
{
protected:

  // normalizing function
  virtual double
  norm (const point& p);

};


#endif
