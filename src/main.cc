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
  string seq = argc <= 1 ? create_murpi('A', 'E') : argv[1];
  string sgn = argc <= 2 ? murpi2sign (seq.data()) : argv[2];
  string way = murpi2way (seq, sgn);
  points path = way2path (way, nails);
  points bezier = SimpleNormedCubicBezier().calc (path, 100);

  cout << sgn << endl << seq << endl;
  cout << endl << way << endl;

  ofstream f ("test.ps");
  PS::init (f);
  PS::unit (f, 3.6);

  PS::lineWidth (f, 0);
  PS::rect (f, 24, 100, 0.2, nails);
  PS::curve (f, 24, 100, false, false, path);
  PS::showpage (f);

  PS::lineWidth (f, 0);
  PS::rect (f, 24, 100, 0.2, nails);
  PS::curve (f, 24, 100, false, false, bezier);
  PS::showpage (f);

  f.close ();
  system ("gv test.ps");

  return 0;
}
