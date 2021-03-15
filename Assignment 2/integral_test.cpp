//  file: integ_test.cpp
//
//  This is a test program for basic integration methods.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  changed functions to pass integrand
//      09-Jan-2011  updated functions
//
//  Notes:
//   * define with floats to emphasize round-off error
//   * compile with:  "g++ -Wall -c integ_test.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez
//             copyrighted by John Wiley and Sons, New York
//             code copyrighted by RH Landau
//
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

using namespace std;

#include "integral_routines.h"	// prototypes for integration routines

double my_integrand (double x);

double my_integrand_gsl (double x, void *params);

//************************************************************************

int
main (void)
{
  // set up the integration specifiction
  const int max_intervals = 501;	// maximum number of intervals
  const float lower = 0.0;	// lower limit of integration
  const float upper = 1.0;	// upper limit of integration

  const double answer = 4.0;	// the "exact" answer for the test
  float result = 0.;  // approximate answer

  // open the output to 3 file streams
  ofstream milne_out ("milne_int.dat");	// save data in milne_int.dat
  ofstream simpson_out ("simpson_int.dat");	// save data in simpson_int.dat
  // ofstream gsl_out ("gsl_int.dat");	// save data in gsl_int.dat

  milne_out << "#  N       Milne  " << endl;
  milne_out << "#-----------------------------------------" << endl;

  simpson_out << "#  N       Simpson  " << endl;
  simpson_out << "#-----------------------------------------" << endl;


  // gsl_out << "#  N       GSL  " << endl;
  // gsl_out << "#-----------------------------------------" << endl;

  // Simpson/Milnes rule require an odd number of intervals
  for (int i = 5; i <= max_intervals; i += 4)
  {
    milne_out << setw(10) << log10 (i);

    result = milne_rule (i, lower, upper, &my_integrand);
    milne_out << "  " << scientific << log10 (fabs ((result - answer) / answer));

    milne_out << endl;
  }
  milne_out.close ();

  for (int i = 3; i <= max_intervals; i += 2 )
  {
    simpson_out << setw(10) << log10 (i);
    result = simpsons_rule (i, lower, upper, &my_integrand);
    simpson_out << "  " << scientific << log10 (fabs ((result - answer) / answer));
    simpson_out << endl;
  }
  simpson_out.close ();

// for (int i =2; i <=max_intervals; i += 2)
// {
//   gsl_out << setw(10) << log10 (i);
//   result = gsl_integrand (i, lower, upper, &gsl_integrand);
//   gsl_out << "  " << scientific << log10 (fabs ((result - answer) / answer));
//   gsl_out << endl;
// }
//   gsl_out.close ();

  cout << "data stored in milne_integ.dat, simpson_integ.dat and gsl_int.dat";

  return (0);
}

//************************************************************************

// the function we want to integrate
double
my_integrand (double x)
{
  return ((log (1. * x))/ sqrt (x));
}

// same function, but for GSL
double
my_integrand_gsl (double x, void *params)
{
  // The next line recovers alpha from the passed params pointer
  double alpha = *(double *) params;

  return (log (alpha * x) / sqrt (x));
}
