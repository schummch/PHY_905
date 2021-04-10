//  file: integral_test.cpp
//
//  This is a test program for basic integration methods.
//
//  Programmer:  Chrissy Schumm schummch@msu.edu
//
//  Revision history:
//    24-March-2021 finally got this to compile :,)
//
//	Comments:
//   compile with make_integral_test
//
//	Analysis of graphs:
// 	Part b:	Region of linear (logrithamic) slopes: Milne = -6.0 (x= 0.75-3.0) Simpsons = -5.9.  This is logical for the Milne rule however unexpected
// 	for the Simpsons rule. In the linear region the error should match the order of the truncation of the taylor series. For the Milne
// 	there is 5 terms giving N^5, however the rule is that the error propogates as N+1, thus a slope of 6 is exactly what is to be expected
// 	for the Milne rule. I believe this is because I chose a very high order polynomial, generally these methods work the best for polynomials
// 	similar in order to their truncation values, this is why I suspect the simpsons failed. As for round off error I am not sure why it is so
// flat, it should be proportional to the square root of the truncation error but in both cases it is simply zero. I think this means both methods
// 	are still consistent approximations in this region. Finally for the error I chose to do the empirical analysis. The slope of the curve exactly
// 	m = 6, which is the truncation error, so this shows it is a reliable method of approximations even when an exact anwser is not known.
//
// 	Part c: For both Milne and Simpsons the optimal value is around N = 2800, this is the minima in the relative error functions before the
// 	round off error begins.  As for a more analytic approach you can look at the value of the log plot. We know that doubles are reliable to 10-16
// 	which is exactly where the plot flattens and begins round off. Theoretically based on the session 3 notes the value should be roughly 2511 steps
// 	I would consider this to be a pretty good estimate and that the theory is generally in agreement with the practice.
//
//
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

#include "integral_routines.h"

// prototypes for integration routines

double my_integrand (double x);

double my_gsl_integrand (double x, void *params);


//************************************************************************

int
main (void)
{
  // set up the integration specifiction
  const int max_intervals = 1501;	// maximum number of intervals
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration

  const double answer = 3.141592;	// the "exact" answer of the integral
  double result = 0.;  // approximate answer double


  // Simpson's rule requires an odd number of intervals
  ofstream simpson_out ("simpson_int.dat");	// save Simpsons data in simpson_int.dat

  simpson_out  << "#  N                                      Simpsons " << endl;
  simpson_out  << "#--------------------------------------------------" << endl;


  for (int i = 3; i <= max_intervals; i += 2)
  {
    simpson_out  << setw(16) << log10(i) << "  ";

    result = simpsons_rule (i, lower, upper, &my_integrand);
    simpson_out << "  " << scientific << log10 (fabs ((result - answer) / answer));

    simpson_out  << endl;
  }

	simpson_out .close ();

  // Milnes's rules requires an odd number of intervals
  ofstream milne_out ("milne_int.dat");		// save milne data in milne_int.dat

  milne_out  << "#  N                                      Milne " << endl;
  milne_out  << "#--------------------------------------------------" << endl;

  for (int i = 5; i <= max_intervals; i += 4)
    {
      milne_out  << setw(16) << log10(i) << "  ";

      result = milne_rule (i, lower, upper, &my_integrand); //printing the Milne error with error value computed simultaneosly
      milne_out << "  " << scientific << log10 (fabs ((result - answer) / answer));

      milne_out  << endl;
    }

  milne_out .close ();

//*********************************************************************************************

  ofstream gsl_out ("gsl_int.dat");	// save gsl data in gsl_int.dat

  gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (10000);

  double lower_limit = 0;	/* lower limit a */
  double upper_limit = 1;	/* upper limit b */
  double abs_error = 1.0e-8;	/* to avoid round-off problems */
  double rel_error = 1.0e-8;	/* the result will usually be much better */
  double resultgsl;		/* the result from the integration */
  double error;			/* the estimated error from the integration */

  double alpha = 1.0;		// parameter in integrand
  double expected = 3.141592;	// exact answer

  gsl_function My_function;
  void *params_ptr = &alpha;

  My_function.function = &my_gsl_integrand;
  My_function.params = params_ptr;

  gsl_integration_qags (&My_function, lower_limit, upper_limit,
			abs_error, rel_error, 10000, work_ptr, &resultgsl,
			&error);

  gsl_out << "actual error = " << log10(fabs(resultgsl - expected)) << endl;
  gsl_out << "intervals = " << work_ptr->size << endl;

gsl_out .close();

  cout << "data stored in 3 .dat files";  //printing out that data storage was successful

  return (0);
}

//************************************************************************

//Integrand for milne and simpson
double
my_integrand (double x)
{
  return (sin(x) * sin(x));
}

  // Same function, but for GSL

 double my_gsl_integrand (double x, void *params)
 {
   double alpha = *(double *) params;
   return (sin(x) * sin(x*alpha));
 }
