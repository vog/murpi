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

protected:

  virtual void
  print (ostream& out) = 0;

public:

  static ostream&
  init (ostream& out, const char* mediaType = "letter", int orientation = 0,
	double un = 72);

  static ostream&
  unit (ostream& out, double un = 72);

  static ostream&
  lineWidth (ostream& out, double width = 1);

  static ostream&
  showpage (ostream& out);

  static ostream&
  gsave (ostream& out);

  static ostream&
  grestore (ostream& out);

  static ostream&
  rect (ostream &out, double offx, double offy, double width,
	const points& rects);

  static ostream&
  curve (ostream& out, double offx, double offy, bool close, bool fill,
	 const points& path);

};


#endif
