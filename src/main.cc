#include <config.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include "murpi.h"
#include "point.h"
#include "bezier.h"
#include "ps.h"


/*
 * about
 */

void
about ()
{
  cout << endl
       << "   Murpi - Murphistic Images" << endl
       << "   =========================" << endl
       << endl
       << "   Version " VERSION << endl
       << endl
       << "   (C) " COPYRIGHT << endl
       << endl
       << "   This program is free software; you can redistribute it and/or modify" << endl
       << "   it under the terms of the GNU General Public License as published by" << endl
       << "   the Free Software Foundation; either version 2 of the License, or" << endl
       << "   (at your option) any later version." << endl
       << endl
       << "   This program is distributed in the hope that it will be useful," << endl
       << "   but WITHOUT ANY WARRANTY; without even the implied warranty of" << endl
       << "   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << endl
       << "   GNU General Public License for more details." << endl
       << endl
       << "   You should have received a copy of the GNU General Public License" << endl
       << "   along with this program; if not, write to the Free Software" << endl
       << "   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA" << endl
       << endl;
}


/*
 * main program
 */

int
main (int argc, char* argv[])
{
  about ();

  cout << "calculating ." << flush;
  int const num = 22;
  string c = create_murpi ('A', 'A'+num-1);
  cout << "." << flush;
  ofstream out ("murpi.txt");
  out << "(" << num << "-" << c.length () << ") " << c << " <"
      << (test_murpi (c.data (), 'A', 'A'+num-1) ? "yeah" : "D'OH!")
      << ">" << endl;
  cout << "." << flush;
  out << "(" << num << "-" << c.length () << ") " << murpi2sign (c) << endl;
  cout << ". ready  (output to murpi.txt)" << endl << endl;

  points nails = create_nails (7, 40);
  string murpi = argc <= 1 ? create_murpi ('A', 'G') : argv[1];
  string sign = argc <= 2 ? murpi2sign (murpi) : argv[2];
  string way = murpi2way (murpi, sign);
  points path = way2path (way, nails);
  points bezier = SimpleNormedCubicBezier().calc (path, 100);

  cout << sign << endl << murpi << endl;
  cout << endl << way << endl;

  ofstream f ("murpi.ps");
  PS::init (f, "a4", 0, 2.5);

  PS::landscape (f);
  PS::lineWidth (f, 0);
  PS::setfont (f, "Courier", 7);
  PS::show (f, 10, -18, sign);
  PS::show (f, 10, -20, murpi);
  PS::rect (f, 70, -100, 0.2, nails);
  path.setBounds (rect (10, -21, 330, -230));
  PS::curve (f, 0, 0, false, false, path);
  PS::showpage (f);

  PS::landscape (f);
  PS::lineWidth (f, 0);
  PS::setfont (f, "Courier", 7);
  PS::show (f, 10, -18, sign);
  PS::show (f, 10, -20, murpi);
  PS::rect (f, 70, -100, 0.2, nails);
  bezier.setBounds (rect (10, -21, 330, -230));
  PS::curve (f, 0, 0, false, false, bezier);
  PS::showpage (f);

  nails = create_nails (4, 30);
  murpi = create_murpi ('A', 'D');
  sign = murpi2sign (murpi);
  way = murpi2way (murpi, sign);
  path = way2path (way, nails);
  bezier = SimpleNormedCubicBezier ().calc (path, 100);

  PS::landscape (f);
  PS::lineWidth (f, 0);
  PS::setfont (f, "Courier", 32);
  PS::show (f, 10, -10, sign);
  PS::show (f, 10, -18, murpi);
  PS::show (f, 10, -35, way);
  PS::rect (f, 70, -100, 0.2, nails);
  path.setBounds (rect (40, -50, 330, -230));
  PS::curve (f, 0, 0, false, false, path);
  PS::showpage (f);

  PS::landscape (f);
  PS::lineWidth (f, 0);
  PS::setfont (f, "Courier", 32);
  PS::show (f, 10, -10, sign);
  PS::show (f, 10, -18, murpi);
  PS::show (f, 10, -35, way);
  PS::rect (f, 70, -100, 0.2, nails);
  bezier.setBounds (rect (40, -50, 330, -230));
  PS::curve (f, 0, 0, false, false, bezier);
  PS::showpage (f);

  f.close ();

  cout << endl << "... ready  (output to murpi.ps)" << endl << endl;

  return 0;
}
