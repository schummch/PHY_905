//  file: mc_integration.cpp
//
//  Program to illustrate Monte Carlo integration
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      06-Mar-2004  original version (from mc_integration.c)
//      25-Feb-2012  switched functions and eliminated trials
//
//  Notes:
//   * random numbers are generated uniformly from lower to upper
//   * uses the GSL random number functions
//   * both the gsl_rng.h and gsl_randist.h header files are needed
//   * the current version uses the gsl_rng_taus random number
//      generator.  There are many other choices (see the GSL manual).
//
//******************************************************************

// include files
#include <iostream>		// cout and cin
#include <iomanip>		// manipulators like setprecision
#include <fstream>		// file input and output
using namespace std;		// we need this when .h is omitted
#include <cmath>

#include <gsl/gsl_rng.h>	// GSL random number generators
#include <gsl/gsl_randist.h>	// GSL random distributions

// function prototypes
extern unsigned long int random_seed ();	// routine to generate a seed
inline double sqr (double x) {return (x*x);};  // to square x

// integrand for uniform sampling
double integrand1(gsl_rng *rng_ptr, int dim, double sigma, double lower,
                  double upper);

//********************************************************************
int
main (void)
{
  const double lower = -5.;	    // lower limit of integration for uniform
  const double upper = 5.;	    // upper limit of integration for uniform
  const double sigma = 1.;          // constant in gaussian
  const int dim = 10;                // dimension of the integral
  double exact = double(dim)*sqr(sigma);   // exact answer from Mathematica

  int Nvec = 0;		        // number of vectors used to evaluate integral
  int Nvec_min = 10;            // mininum # of vectors to use
  int Nvec_max = 1000000;        // maximum # of vectors to us
  unsigned long int seed;
  gsl_rng *rng_ptr;		// declare pointer to random number
                                //   generator (rng)
  rng_ptr = gsl_rng_alloc (gsl_rng_taus);	// allocate the rng

  seed = random_seed ();    // generate a seed
  cout << " Using " << seed << " to seed the RNG" << endl;
  gsl_rng_set (rng_ptr, seed);	// seed the rng

  // output file mc_integration.dat has data on the average R
  ofstream out;
  out.open ("mc_integration.dat");

  cout << endl << "  Nvec   estimate  exact    rel. error " << endl;
  for (Nvec = Nvec_min; Nvec <= Nvec_max; Nvec *= 2)
  {
    double integral_avg = 0;	// reset integral to zero
    for (int j = 0; j < Nvec; j++)
    {
       // sample integrand1 (uniform sampling)
       integral_avg += integrand1(rng_ptr,dim,sigma,lower,upper);
    }
    integral_avg = pow((upper - lower),dim) * integral_avg / double(Nvec);

    cout << setw(6) << Nvec << "   " << fixed << setprecision(4)
         << setw(7) << integral_avg
	 << "   " << exact
	 << "   " << scientific << abs(integral_avg-exact)/exact << endl;
    out << Nvec << " " << fixed << setprecision(8)
        << integral_avg << " " << exact << endl;
  }

  cout << endl << "Data also output to mc_integration.dat." << endl;

  gsl_rng_free (rng_ptr);	// free the random number generator
  out.close ();			// close the output file

  return 0;
}

//********************************************************************
double
integrand1(gsl_rng *rng_ptr, int dim, double sigma, double lower, double upper)
{
  // integrand: 1/sqrt(2pi*sigma^2) (x1+x2+...)^2 e^(-(x1^2+x2^2+...)/sigma^2)
  // uniform sampling of the integrand for x_i's between lower and upper
  double x_sum = 0;
  double xsq_sum = 0;

  for (int k = 1; k <= dim; k++)      // 3 dimensional
  {
    double x_tmp = gsl_ran_flat (rng_ptr, lower, upper);
    x_sum += x_tmp;
    xsq_sum += x_tmp*x_tmp;
  }

  double factor = 1./sqrt(2.*M_PI*sqr(sigma));
  return (pow(factor,dim)*(x_sum * x_sum)*exp(-xsq_sum/(2.*sqr(sigma))));
}

//********************************************************************
