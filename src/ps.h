#ifndef __PS_HEADER
#define __PS_HEADER


#include <config.h>
#include <iostream>
#include "point.h"


/*
 * a PostScript class
 */

class PS
{
public:

  friend ostream&
  operator << (ostream& out, PS* ps);

  virtual
  ~PS () {};

public:

  // initialization
  static ostream&
  init (ostream& out, const char* mediaType = "letter", int orientation = 0,
	double un = 72);

  // sets length unit
  static ostream&
  unit (ostream& out, double un = 72);

  // sets line width
  static ostream&
  lineWidth (ostream& out, double width = 1);

  // shows current page
  static ostream&
  showpage (ostream& out);

  // saves current state
  static ostream&
  gsave (ostream& out);

  // restores saved state
  static ostream&
  grestore (ostream& out);

  // draws some rectangles
  static ostream&
  rect (ostream &out, double offx, double offy, double width,
	points const& rects);

  // draws a curve
  static ostream&
  curve (ostream& out, double offx, double offy, bool close, bool fill,
	 points const& path);

};


#endif
