#include <config.h>
#include <fstream>
#include "murpi.h"


/*
 * main program
 */

int
main (int argc, char *argv[])
{
  const int num = 18;
  string c = create_murphy ('A', 'A'+num-1);
  cout << "(" << num << "-" << c.length () << ") " << c << " <"
       << (test_murphy (c.data (), 'A', 'A'+num-1) ? "yeah" : "D'OH!")
       << ">" << endl;
  cout << "(" << num << "-" << c.length () << ") " << sign_murphy (c.data ()) << endl;

  points nails = create_nails (7);
  string seq = argc <= 1 ? create_murphy('A', 'E') : argv[1];
  string sgn = argc <= 2 ? sign_murphy (seq.data()) : argv[2];
  string way = murpi2way (seq,sgn);

  cout << sgn << endl << seq << endl;
  cout << endl << way << endl;

  ofstream f ("test.ps");
  points2ps (f, nails, way2points (way, nails));
  points2ps (f, nails, way2points (way, nails));
  f.close ();
  system ("gv test.ps");

  return 0;
}
