#include <config.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "point.h"
#include "murpi.h"


/*
 * tests whether "seq" would cause a small crash
 */

bool
test_whoops (const char *seq)
{
  for (; *seq; seq++)
    {
      if (seq[0] == seq[1]) return true;
    }
  return false;
}


/*
 * tests whether "seq" would cause a crash without "ign"
 */

bool
_test_crash (const char *seq, char ign)
{
  stack<char> s;

  for (; *seq; seq++)
    {
      if (*seq != ign)
	{
	  if (s.empty () || s.top () != *seq)
	    s.push (*seq);
	  else
	    s.pop ();
	}
    }

  return s.empty ();
}


bool
test_crash (const char* seq, char ign)
{
  char s[strlen (seq)];
  char *p = s;

  for (; *seq; seq++)
    {
      if (*seq != ign)
	{
	  if (p == s || *(p-1) != *seq)
	    *p++ = *seq;
	  else
	    p--;
	}
    }

  return p == s;
}


/*
 * tests whether "seq" is murphistic
 */

bool
test_murphy (const char* seq, char start, char end)
{
  for (char c = start; c <= end; c++)
    {
      if (!test_crash (seq, c)) return false;
    }

  return true;
}


/*
 * create a murphistic sequence.
 */

string
create_murphy (char start, char end)
{
  string s;
  s += start;
  for (char c = start + 1; c <= end; c++)
    {
      s += c;
      for (int i = s.length() - 2; i >= 0; i--)
	s += s[i];
      s += c;
    }
  return s;
}


/*
 * create the +/- of a murphistic sequence.
 */

string
sign_murphy (const char* seq)
{
  string s (seq);
  int l = strlen (seq);
  s[0] = '+';
  for (;;)
    {
      // search next unsigned nail
      int i;
      char n;
      for (i=1; i<l && ((n=s[i])=='+' || n=='-'); i++);
      if (i>=l) return s;

      // sign all nails of this kind
      char c='+';
      for (; i<l; i++)
	if (seq[i]==n)
	  s[i] = (c = '+'+'-'-c);
    }
}


/*
 * murpi -> way
 */

string
murpi2way (const string seq, const string sgn)
{
  string s;

  for (uint i = 1; i < seq.length (); i++)
    {
      int d = seq[i] - seq[i-1];
      if (d == 0)
	{
	  s += (sgn[i-1] == sgn[i]) ? "OO" : "|";
	}
      else
	{
	  char c = d > 0 ? '+' : '-';
	  d = abs(d);
	  if (sgn[i-1] != c) s += 'O';
	  for (int j = 1; j < d; j++) s += '_';
	  s += (sgn[i] != c) ? "_O" : "-";
	}
    }

  return s;
}


/*
 * create num nails
 */

points
create_nails (int num)
{
  points p;
  for (int i = 0; i < num; i++)
    {
      p.add (30*i, 0);
    }
  return p;
}


/*
 * way -> points
 */

class way_params
{
private:
  int up,down,left,right;

public:
  way_params ()
  {
    up = down = left = right = 0;
  }

  int &
  x (int dx)
  {
    return dx > 0 ? right : left;
  }

  int &
  y (int dy)
  {
    return dy > 0 ? up : down;
  }
};

points
way2points (const string way, const points nails)
{
  points p;
  map<int,way_params> m;
  int n = 0;       // current nail
  int x = +1;      // x direction
  int y = +1;      // y direction

  m[n].y(y)++;
  p.add (nails[n].x - 20, -100);
  p.add (nails[n].x, nails[n].y + y*m[n].y(y));
  for (uint i = 0; i < way.length(); i++)
    {
      switch (way[i])
	{
	case '-':
	  n += x;
	  y = +1;
	  m[n].y(y)++;
	  p.add (nails[n].x, nails[n].y + y*m[n].y(y));
	  break;

	case '_':
	  n += x;
	  y = -1;
	  m[n].y(y)++;
	  p.add (nails[n].x, nails[n].y + y*m[n].y(y));
	  break;

	case 'O':
	  y = -y;
	  m[n].x(x)++;
	  m[n].y(y)++;
	  p.add (nails[n].x + x*m[n].x(x), (m[n].y(+1) - m[n].y(-1)) / 2);
	  p.add (nails[n].x, nails[n].y + y*m[n].y(y));

	case '|':
	  x = -x;
	  break;
	}
    }
  p.add (nails[n].x + 20, -100);

  return p;
}


/*
 * path -> bezier
 */

void
line2bezier (const point p0, const point p1, const point p2, const point p3,
	     points &bezier, int depth)
{
  double ax = -1 * p0.x +1 * p1.x -1 * p2.x +1 * p3.x;
  double bx = +2 * p0.x -2 * p1.x +1 * p2.x -1 * p3.x;
  double cx = -1 * p0.x           +1 * p2.x;
  double dx =           +1 * p1.x;

  double ay = -1 * p0.y +1 * p1.y -1 * p2.y +1 * p3.y;
  double by = +2 * p0.y -2 * p1.y +1 * p2.y -1 * p3.y;
  double cy = -1 * p0.y           +1 * p2.y;
  double dy =           +1 * p1.y;

  for (double i = 0, d = 1.0/depth; i <= 1; i += d)
    {
      bezier.add ((((ax * i + bx) * i) + cx) * i + dx,
		  (((ay * i + by) * i) + cy) * i + dy);
    }
}


/*
 * points -> bezier
 */

points
path2bezier (points path, int depth)
{
  points p;

  path.insert (path.begin(), path[0]);
  path.insert (path.begin(), path[0]);
  path.insert (path.end(), path[path.size () - 1]);
  path.insert (path.end(), path[path.size () - 1]);

  for (uint i = 0, s = path.size (); i + 3 < s; i++)
    {
      line2bezier (path[i], path[i+1], path[i+2], path[i+3], p, depth);
    }

  return p;
}


/*
 * searches all murphy sequences of a given length in the given range
 */

void
search_murphy (int length, char start, char end)
{
  char s[length+1];
  char *t = s;
  int n = 0;

  s[length] = 0;
  for (;;)
    {
      for (; t < s+length; t++) *t = start;

      if (!test_whoops (s)
	  && test_murphy (s, start, end))
	cout << "(" << ++n << ")\t" << s << endl;

      for (t--; t >= s && *t == end; t--);
      if (t < s) break;

      (*t)++;
      t++;
    }

  cout << endl;
}
