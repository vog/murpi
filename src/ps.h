#ifndef __PS_HEADER
#define __PS_HEADER


#include <config.h>
#include <string>
#include <iostream>
#include "point.h"


/*
 * a PostScript class
 */

class PS
{
public:

  friend std::ostream&
  operator << (std::ostream& out, PS* ps);

  virtual
  ~PS () {};

public:

  // initialization
  static std::ostream&
  init (std::ostream& out, char const* mediaType = "letter", int orientation = 0,
	double un = 72);

  // sets length unit
  static std::ostream&
  unit (std::ostream& out, double un = 72);

  // sets landscape output
  static std::ostream&
  landscape (std::ostream& out);

  // sets line width
  static std::ostream&
  lineWidth (std::ostream& out, double width = 1);

  // sets font
  static std::ostream&
  setfont (std::ostream& out, char const* font, int size);

  // shows current page
  static std::ostream&
  showpage (std::ostream& out);

  // saves current state
  static std::ostream&
  gsave (std::ostream& out);

  // restores saved state
  static std::ostream&
  grestore (std::ostream& out);

  // draws text
  static std::ostream&
  show (std::ostream& out, double x, double y, char const* text);

  // draws text
  static std::ostream&
  show (std::ostream& out, double x, double y, std::string const& text);

  // draws some rectangles
  static std::ostream&
  rect (std::ostream &out, double offx, double offy, double width,
	points const& rects);

  // draws a curve
  static std::ostream&
  curve (std::ostream& out, double offx, double offy, bool close, bool fill,
	 points const& path);

};


#endif
