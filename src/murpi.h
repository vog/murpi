#ifndef __MURPI_HEADER
#define __MURPI_HEADER


#include <config.h>
#include <iostream>
#include <string>
#include <vector>
#include "point.h"


/*
 * tests whether "seq" would cause a small crash
 */

bool
test_whoops (const char* seq);


/*
 * tests whether "seq" would cause a crash without "ign"
 */

bool
test_crash (const char* seq, char ign);


/*
 * tests whether "seq" is murphistic
 */

bool
test_murphy (const char* seq, char start, char end);


/*
 * create a murphistic sequence.
 */

string
create_murphy (char start, char end);


/*
 * create the +/- of a murphistic sequence.
 */

string
sign_murphy (const char* seq);


/*
 * murpi -> way
 */

string
murpi2way (const string seq, const string sgn);


/*
 * create num nails
 */

points
create_nails (int num);


/*
 * way -> points
 */

points
way2points (const string way, const points nails);


/*
 * points -> bezier
 */

points
path2bezier (const points path, int depth);


/*
 * points -> PostScript
 */

void
points2ps (ostream &o, const points nails, const points path);


/*
 * searches all murphy sequences of a given length in the given range
 */

void
search_murphy (int length, char start, char end);

#endif
