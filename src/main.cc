#include <config.h>
#include <fstream>
#include "murpi.h"
#include "point.h"
#include "bezier.h"
#include "ps.h"


/*
 * main program
 */

int
main (int argc, char* argv[])
{
  int const num = 18;
  string c = create_murpi ('A', 'A'+num-1);
  cout << "(" << num << "-" << c.length () << ") " << c << " <"
       << (test_murpi (c.data (), 'A', 'A'+num-1) ? "yeah" : "D'OH!")
       << ">" << endl;
  cout << "(" << num << "-" << c.length () << ") " << murpi2sign (c.data ()) << endl;

  points nails = create_nails (7);
  string murpi = argc <= 1 ? create_murpi ('A', 'E') : argv[1];
  string sign = argc <= 2 ? murpi2sign (murpi.data ()) : argv[2];
  string way = murpi2way (murpi, sign);
  points path = way2path (way, nails);
  points bezier = SimpleNormedCubicBezier().calc (path, 100);

  cout << sign << endl << murpi << endl;
  cout << endl << way << endl;

  ofstream f ("murpi.ps");
  PS::init (f, "a4", 1, 3.6);

  PS::lineWidth (f, 0);
  PS::rect (f, 24, 150, 0.2, nails);
  PS::curve (f, 24, 150, false, false, path);
  PS::showpage (f);

  PS::lineWidth (f, 0);
  PS::rect (f, 24, 150, 0.2, nails);
  PS::curve (f, 24, 150, false, false, bezier);
  PS::showpage (f);

  f.close ();
  system ("gv -landscape murpi.ps");

  return 0;
}
