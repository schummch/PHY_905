//  file: integral_test.cpp
//
//  These are routines for Simpson, Milne and GSL integration methods
//
//  Programmer:  Nathan Jansen  jansenn1@msu.edu
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  changed functions to pass integrand
//      09-Jan-2011  updated functions
//
//  Notes:
//   compile with make_integral_test
//
//
//
//
//
//************************************************************************

// include files
#include <cmath>
#include "integral_routines.h"   // integration routine prototypes



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


//	Integration using Milne rule
double milne_rule ( int num_pts, double x_min, double x_max,
                      double (*integrand) (double x) )
{
   double interval = ((x_max - x_min)/double(num_pts - 1));  // called h in notes
   double sum=  0.;  // initialize integration sum to zero
   double x1, x2, x3, x4;
   for (int n=2; n<num_pts; n+=4)  // step through the integral, 4 points at a time  Start at 7 because it looks the nicest, possibly due to weirdness in the end points
   {
	 // this loop is to set up the h values in the interval, from section 3 notes, 64h/45, 24h/45, 64h/45, (14h/45 + 14h/45)
     x1 = x_min + interval * double (n-1);  //Milne requires 4 points to compute, this is point 1, using to loop to find the nth interval
     x2 = x1 + interval;
	 x3 = x2 + interval;
	 x4 = x3 + interval;

     sum += (64.)*integrand(x1) + (24.)*integrand(x2) + (64.)*integrand(x3) + (28.)*integrand(x4);
   }
   sum += 14.* (integrand(x_min) + (integrand(x_max)));    //end points multiplied by 14
   sum *= (interval/45.);									// multiplying by h/45 to make it all have the form (x)h/45

 return (sum);
}
