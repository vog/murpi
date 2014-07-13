#include <config.h>
#include <string>
#include <iostream>
#include "point.h"
#include "ps.h"


/*
 * initialization
 */

std::ostream&
PS::init (std::ostream& out, char const* mediaType, int orientation, double un)
{
  return out << "%!" << std::endl
	     << "<< /MediaType {" << mediaType
	     << "} /Orientation " << orientation
	     << " >> setpagedevice" << std::endl
	     << "/un {" << un << " mul} def" << std::endl
	     << "/Times-Roman findfont" << std::endl
	     << "12 scalefont" << std::endl
	     << "setfont" << std::endl;
}


/*
 * sets length unit
 */

std::ostream&
PS::unit (std::ostream& out, double un)
{
  return out << "/un {" << un << " mul} def" << std::endl;
}


/*
 * sets landscape output
 */

std::ostream&
PS::landscape (std::ostream& out)
{
  return out << "90 rotate" << std::endl;
}


/*
 * sets line width
 */

std::ostream&
PS::lineWidth (std::ostream& out, double width)
{
  return out << width << " setlinewidth" << std::endl;
}


/*
 * sets font
 */

std::ostream&
PS::setfont (std::ostream& out, char const* font, int size)
{
  return out << "/" << font << " findfont" << std::endl
	     << size << " scalefont" << std::endl
	     << "setfont" << std::endl;
}


/*
 * shows current page
 */

std::ostream&
PS::showpage (std::ostream& out)
{
  return out << "showpage" << std::endl;
}


/*
 * saves current state
 */

std::ostream&
PS::gsave (std::ostream& out)
{
  return out << "gsave" << std::endl;
}


/*
 * restores saved state
 */

std::ostream&
PS::grestore (std::ostream& out)
{
  return out << "grestore" << std::endl;
}


/*
 * draws text
 */

std::ostream&
PS::show (std::ostream& out, double x, double y, char const* text)
{
  return out << "newpath" << std::endl
	     << x << " un " << y << " un moveto" << std::endl
	     << "(" << text << ") show" << std::endl;
}


/*
 * draws text
 */

std::ostream&
PS::show (std::ostream& out, double x, double y, std::string const& text)
{
  return out << "newpath" << std::endl
	     << x << " un " << y << " un moveto" << std::endl
	     << "(" << text << ") show" << std::endl;
}


/*
 * draws some rectangles
 */

std::ostream&
PS::rect (std::ostream& out, double offx, double offy, double width,
	  points const& rects)
{
  for (uint i = 0; i < rects.size(); i++)
    {
      out << "newpath" << std::endl
	  << offx + rects[i].x - width/2 << " un "
	  << offy + rects[i].y - width/2 << " un moveto" << std::endl
	  << width << " un " << 0 << " un rlineto" << std::endl
	  << 0 << " un " << width << " un rlineto" << std::endl
	  << -width << " un " << 0 << " un rlineto" << std::endl
	  << "closepath" << std::endl
	  << "fill" << std::endl;
    }
  return out;
}


/*
 * draws a curve
 */

std::ostream&
PS::curve (std::ostream& out, double offx, double offy, bool close, bool fill,
	   points const& path)
{
  out << "newpath" << std::endl;
  for (uint i = 0, s = path.size (); i < s; i++)
    {
      out << offx + path[i].x << " un " << offy + path[i].y << " un "
	  << (i == 0 ? "moveto" : "lineto") << std::endl;
    }
  if (close) out << "closepath" << std::endl;
  out << (fill ? "fill" : "stroke") << std::endl;
  return out;
}
