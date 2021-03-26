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
  float result = 0;  // approximate answer

  // open the output to 3 file streams
  ofstream milne_out ("milne_int.dat");	// save data in milne_int.dat
  ofstream simpson_out ("simpson_int.dat");	// save data in simpson_int.dat
  ofstream gsl_out ("gsl_int.dat");	// save data in gsl_int.dat

  milne_out << "#  N       Milne  " << endl;
  milne_out << "#-----------------------------------------" << endl;

  simpson_out << "#  N       Simpson  " << endl;
  simpson_out << "#-----------------------------------------" << endl;


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

//************************************************************************

gsl_out << "#  N       GSL  " << endl;
gsl_out << "#-----------------------------------------" << endl;


for (int i = 3; i <= max_intervals; i += 2 )
{
  gsl_out << setw(10) << log10 (i);
  result = my_gsl_integration_qags (lower, upper, &my_integrand_gsl);
  gsl_out << "  " << scientific << log10 (fabs ((result - 4.0) / 4.0));
  gsl_out << endl;
}
gsl_out.close ();

  // Integration using GSL
  // double my_gsl_integration_qags (double x_min, double x_max,
  //   double (*integrand)(double x, void* params_ptr))
  //   {
  //   gsl_integration_workspace *work_ptr
  //     = gsl_integration_workspace_alloc (1000);
  //
  //   double lower_limit = x_min;	/* lower limit a */
  //   double upper_limit = x_max;	/* upper limit b */
  //   double abs_error = 1.0e-8;	/* to avoid round-off problems */
  //   double rel_error = 1.0e-8;	/* the result will usually be much better */
  //   double result;		/* the result from the integration */
  //   double error;			/* the estimated error from the integration */
  //
  //   double alpha = 1.0;		// parameter in integrand
  //   // double expected = -4.0;	// exact answer
  //
  //   gsl_function My_function;
  //   void *params_ptr = &alpha;
  //
  //   My_function.function = &my_integrand_gsl;
  //   My_function.params = params_ptr;
  //
  //   gsl_integration_qags (&My_function, lower_limit, upper_limit,
  // 			abs_error, rel_error, 1000, work_ptr, &result,
  // 			&error);
  //   }
  //
  //   gsl_out << "actual error  = " << log10(fabs(result-4.0)) << endl;
  //   gsl_out << "intervals = " << work_ptr->size << endl;


return (0);
}
//************************************************************************

// the function we want to integrate
double my_integrand (double x)
  {
  return ((log (1. * x))/ sqrt (x));
  }

// same function, but for GSL
double my_integrand_gsl (double x, void *params)
  {
  double alpha = *(double *) params;
  return (log (alpha * x) / sqrt (x));
  }
