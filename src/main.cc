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
  std::cout << std::endl
            << "   Murpi - Murphistic Images" << std::endl
            << "   =========================" << std::endl
            << std::endl
            << "   Version " VERSION << std::endl
            << std::endl
            << "   (C) " COPYRIGHT << std::endl
            << std::endl
            << "   This program is free software; you can redistribute it and/or modify" << std::endl
            << "   it under the terms of the GNU General Public License as published by" << std::endl
            << "   the Free Software Foundation; either version 2 of the License, or" << std::endl
            << "   (at your option) any later version." << std::endl
            << std::endl
            << "   This program is distributed in the hope that it will be useful," << std::endl
            << "   but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl
            << "   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl
            << "   GNU General Public License for more details." << std::endl
            << std::endl
            << "   You should have received a copy of the GNU General Public License" << std::endl
            << "   along with this program; if not, write to the Free Software" << std::endl
            << "   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA" << std::endl
            << std::endl;
}


/*
 * main program
 */

int
main (int argc, char* argv[])
{
  about ();

  std::cout << "calculating ." << std::flush;
  int const num = 22;
  std::string c = create_murpi ('A', 'A'+num-1);
  std::cout << "." << std::flush;
  std::ofstream out ("murpi.txt");
  out << "(" << num << "-" << c.length () << ") " << c << " <"
      << (test_murpi (c.data (), 'A', 'A'+num-1) ? "yeah" : "D'OH!")
      << ">" << std::endl;
  std::cout << "." << std::flush;
  out << "(" << num << "-" << c.length () << ") " << murpi2sign (c) << std::endl;
  std::cout << ". ready  (output to murpi.txt)" << std::endl << std::endl;

  points nails = create_nails (7, 40);
  std::string murpi = argc <= 1 ? create_murpi ('A', 'G') : argv[1];
  std::string sign = argc <= 2 ? murpi2sign (murpi) : argv[2];
  std::string way = murpi2way (murpi, sign);
  points path = way2path (way, nails);
  points bezier = SimpleNormedCubicBezier().calc (path, 100);

  std::cout << sign << std::endl << murpi << std::endl;
  std::cout << std::endl << way << std::endl;

  std::ofstream f ("murpi.ps");
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

  std::cout << std::endl << "... ready  (output to murpi.ps)" << std::endl << std::endl;

  return 0;
}
