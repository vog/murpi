#include <config.h>
#include <iostream>
#include "point.h"
#include "ps.h"


/*
 * initialization
 */

ostream&
PS::init (ostream& out, const char* mediaType, int orientation, double un)
{
  return out << "%!" << endl
	     << "<< /MediaType {" << mediaType
	     << "} /Orientation " << orientation
	     << " >> setpagedevice" << endl
	     << "/un {" << un << " mul} def" << endl;
}


/*
 * set length unit
 */

ostream&
PS::unit (ostream& out, double un)
{
  return out << "/un {" << un << " mul} def" << endl;
}


/*
 * set line width
 */

ostream&
PS::lineWidth (ostream& out, double width)
{
  return out << width << " setlinewidth" << endl;
}


/*
 * show current page
 */

ostream&
PS::showpage (ostream& out)
{
  return out << "showpage" << endl;
}


/*
 * save current state
 */

ostream&
PS::gsave (ostream& out)
{
  return out << "gsave" << endl;
}


/*
 * restore saved state
 */

ostream&
PS::grestore (ostream& out)
{
  return out << "grestore" << endl;
}


/*
 * draws some rectangles
 */

ostream&
PS::rect (ostream& out, double offx, double offy, double width,
	  const points& rects)
{
  for (uint i = 0; i < rects.size(); i++)
    {
      out << "newpath" << endl
	  << offx + rects[i].x - width/2 << " un "
	  << offy + rects[i].y - width/2 << " un moveto" << endl
	  << width << " un " << 0 << " un rlineto" << endl
	  << 0 << " un " << width << " un rlineto" << endl
	  << -width << " un " << 0 << " un rlineto" << endl
	  << "closepath" << endl
	  << "fill" << endl;
    }
  return out;
}


/*
 * draws a curve
 */

ostream&
PS::curve (ostream& out, double offx, double offy, bool close, bool fill,
	   const points& path)
{
  out << "newpath" << endl;
  for (uint i = 0, s = path.size (); i < s; i++)
    {
      out << offx + path[i].x << " un " << offy + path[i].y << " un "
	  << (i == 0 ? "moveto" : "lineto") << endl;
    }
  if (close) out << "closepath" << endl;
  out << (fill ? "fill" : "stroke") << endl;
  return out;
}
