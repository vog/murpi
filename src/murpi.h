#ifndef __MURPI_HEADER
#define __MURPI_HEADER


#include <config.h>
#include <iostream>
#include <string>
#include <vector>
#include "point.h"


/*
 * tests whether "murpi" would cause a small crash
 */

bool
test_whoops (char const* murpi);


/*
 * tests whether "murpi" would cause a crash without "ign"
 */

bool
test_crash (char const* murpi, char ign);


/*
 * tests whether "murpi" is murphistic
 */

bool
test_murpi (char const* murpi, char start, char end);


/*
 * creates a murphistic sequence.
 */

string
create_murpi (char start, char end);


/*
 * creates the +/- of a murphistic sequence.
 */

string
murpi2sign (string const& murpi);


/*
 * murpi -> way
 */

string
murpi2way (string const& murpi, string const& sign);


/*
 * creates num nails
 */

points
create_nails (int num, double dist);


/*
 * way -> path
 */

points
way2path (string const& way, points const& nails);


/*
 * searches all murphy sequences of a given length in the given range
 */

void
search_murphi (int length, char start, char end);


#endif
