#include <config.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "murpi.h"


/*
 * tests whether "seq" would cause a small crash
 */

bool
test_whoops (const char* seq)
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
_test_crash (const char* seq, char ign)
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
sign_murphy (const char *seq)
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

points
way2points (const string way, const points nails)
{
  points p;
  map<int,uint> m;
  int n = 0;       // current nail
  int x = +1;      // x direction
  int y = +1;      // y direction

  m[n] = 1;
  p.add (nails[n].x, nails[n].y+y*m[n]);
  for (uint i = 0; i < way.length(); i++)
    {
      switch (way[i])
	{
	case '-':
	  n += x;
	  m[n]++;
	  y = +1;
	  p.add (nails[n].x, nails[n].y + y*m[n]);
	  break;

	case '_':
	  n += x;
	  m[n]++;
	  y = -1;
	  p.add (nails[n].x, nails[n].y + y*m[n]);
	  break;

	case 'O':
	  y = -y;
	  p.add (nails[n].x + x*m[n], nails[n].y);
	  p.add (nails[n].x, nails[n].y + y*m[n]);

	case '|':
	  x = -x;
	  break;
	}
    }

  return p;
}


/*
 * points -> PostScript
 */

void
points2ps (ostream &o, const points nails, const points path)
{
  double n = 0.2;
  int x = 30;
  int y = 100;
  o << "%!" << endl;
  o << "/un {3.6 mul} def" << endl;
  o << "0 setlinewidth" << endl;

  o << "newpath" << endl;
  o << "0 un 0 un moveto" << endl;
  for (uint i = 0; i < path.size(); i++)
    {
      o << x+path[i].x << " un " << y+path[i].y << " un lineto" << endl;
    }
  o << "160 un 0 un lineto" << endl;
  o << "stroke" << endl;

  for (uint i = 0; i < nails.size(); i++)
    {
      o << "newpath" << endl;
      o << x+nails[i].x-n << " un " << y+nails[i].y-n << " un moveto" << endl;
      o << +2*n << " un " << 0 << " un rlineto" << endl;
      o << 0 << " un " << +2*n << " un rlineto" << endl;
      o << -2*n << " un " << 0 << " un rlineto" << endl;
      o << "closepath" << endl;
      o << "fill" << endl;
    }
  o << "showpage" << endl;
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
