// file: integral_routines.cpp
//
//  These are routines for Simpson (DP), Milne and GSL
//
//  Programmer 1:  Dick Furnstahl  furnstahl.1@osu.edu
//  Programmer 2: Christina Schumm schummch@msu.edu
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  function to be integrated now passed, changed names
//      09-Jan-2011  new names and rearranged; fixed old bug
//      05-Mar-2021  new routines added, changed simpson to double precision
//
//  Notes:
//   * define with floats to emphasize round-off error
//   * compile with:  "g++ -Wall -c integral_routines.cpp" or makefile
//   * adapted from: "Projects in Computational Physics" by Landau and Paez
//             copyrighted by John Wiley and Sons, New York
//             code copyrighted by RH Landau
//   * equation for interval h = (b-a)/(N-1) with x_min=a and x_max=b
//
//************************************************************************

// include files
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include "integral_routines.h"   // integration routine prototypes

#include <gsl/gsl_integration.h>

//************************************************************************

// Integration using Milne rule
double milne_rule ( int num_pts, double x_min, double x_max,
                      double (*integrand) (double x) )
{
   double interval = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero

   double x1, x2, x3, x4;
   for (int n=2; n<num_pts; n+=4)   // step through integral, 4 points at a time
   {
     x1 = x_min + interval * double(n-1);
     x2 = x1 + interval;
     x3 = x2 + interval;
     x4 = x3 + interval;
     sum += (64.)*integrand(x1) + (24.)*integrand(x2) +
            (64.)*integrand(x3) + (28.)*integrand(x4);
   }
  sum += 14. * (x_min - x_max); // set endpoints
  sum *= (interval / 45.);

   return (sum);
}

//************************************************************************

// Integration using Simpson's rule
double simpsons_rule ( int num_pts, double x_min, double x_max,
                      double (*integrand) (double x) )
{
   double interval = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero

   for (int n=2; n<num_pts; n+=2)                // loop for odd points
   {
     double x = x_min + interval * double(n-1);
     sum += (4./3.)*interval * integrand(x);
   }
   for (int n=3; n<num_pts; n+=2)                // loop for even points
   {
     double x = x_min + interval * double(n-1);
     sum += (2./3.)*interval * integrand(x);
   }
   // add in the endpoint contributions
   sum +=  (interval/3.) * (integrand(x_min) + integrand(x_max));

   return (sum);
}

//************************************************************************

// Integration using GSL
  gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (1000);

  double lower_limit = 0;	/* lower limit a */
  double upper_limit = 1;	/* upper limit b */
  double abs_error = 1.0e-8;	/* to avoid round-off problems */
  double rel_error = 1.0e-8;	/* the result will usually be much better */
  double result;		/* the result from the integration */
  double error;			/* the estimated error from the integration */

  double alpha = 1.0;		// parameter in integrand
  double expected = -4.0;	// exact answer

  gsl_function My_function;
  void *params_ptr = &alpha;

  My_function.function = &my_integrand_gsl;
  My_function.params = params_ptr;

  gsl_integration_qags (&My_function, lower_limit, upper_limit,
			abs_error, rel_error, 1000, work_ptr, &result,
			&error);
