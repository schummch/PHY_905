//  file: bessel_A1.cpp
//
//  Spherical Bessel functions via up and down recursion
//
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//  Programmer 2: Christina Schumm schummch@msu.edu
//
//  Revision history:
//      02-Jan-2011  new version, for 780.20 Computational Physics
//      12-Feb-2021
//
//  Notes:
//   * compile with:  make_bessel_A1
//   * adapted from: "Projects in Computational Physics" by Landau and Paez
//             copyrighted by John Wiley and Sons, New York
//             code copyrighted by RH Landau
//   * data saved as: x y1 y2  --- should print column headings!!
//
//  Interpretation of Data:
//  My log/log plot is confusing. Before I did the log/log plot,
// I looked at the relative difference by itself. It seems if the difference
//  was close to one, then the calculation was accurate. For this, the downward
//  recursion worked better.
//
//  I think something went wrong, but I was unable to go to office hours

// Also, all of the pdfs are posted in the Assign_1 folder
//************************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
#include <gsl/gsl_sf_bessel.h>  // gsl Bessel special function header file

using namespace std;		// we need this when .h is omitted

// function prototypes
double down_recursion (double x, int n, int m);	// downward algorithm
double up_recursion (double x, int n);	        // upward algorithm

// global constants
const double xmax = 100.0;	// max of x
const double xmin = 0.1;	// min of x >0
const double step = 0.1;	// delta x
const int order = 10;		// order of Bessel function
const int start = 50;		// used for downward algorithm


//********************************************************************
int main ()
{
  double ans_down, ans_up, y;
  double e_num, e_den, rel_err;
  double e_num_d, e_den_d, rel_err_d;
  double e_num_u, e_den_u, rel_err_u;

  // open an output file stream
  ofstream my_out ("bessel_A1.dat");

  // print out title to screen
  my_out << "# Spherical Bessel functions via up and down recursion"
         << endl;

  my_out <<"#     " << "logx" << "                 "
          << "Up Recursion" << "             "
          << "Down Recursion" << "           "
          << "Compare Up/Down" << "         "
          << "Compare Down/GSL" << "         "
          << "Compare Up/GSL" << endl;

  // step through different x values
  for (double x = xmin; x <= xmax; x += step)
    {
      ans_down = down_recursion (x, order, start);
      ans_up = up_recursion (x, order);
      y = gsl_sf_bessel_J1 (x);   // see the GSL manual for details

      // relative error comparing down/up
      e_num = fabs(ans_up - ans_down);
      e_den = fabs(ans_up) + fabs(ans_down);
      rel_err = e_num / e_den;

      // relative error comparing down/GSL1
      e_num_d = fabs(ans_down - y);
      e_den_d = fabs(ans_down) + fabs(y);
      rel_err_d = e_num_d / e_den_d;

      // relative error comparing down/GSL1
      e_num_u = fabs(ans_up - y);
      e_den_u = fabs(ans_up) + fabs(y);
      rel_err_u = e_num_u / e_den_u;

      my_out << fixed << setprecision (10) << setw (8) << log10(x) << " "
	     << scientific << setprecision (10)
	     << setw (25) << ans_down << " "
	     << setw (25) << ans_up
       << setw (25) << (rel_err)
       << setw (25) << (rel_err_d)
       << setw (25) << (rel_err_u)
       << endl;

    }
  cout << "data stored in bessel_A1.dat." << endl;

  // close the output file
  my_out.close ();
  return (0);
}


//------------------------end of main program-----------------------

// function using downward recursion
double
down_recursion (double x, int n, int m)
{
  double j[start + 2];		// array to store Bessel functions
  j[m + 1] = j[m] = 1.;		// start with "something" (choose 1 here)
  for (int k = m; k > 0; k--)
    {
      j[k - 1] = ((2.* double(k) + 1.) / x) * j[k] - j[k + 1];  // recur. rel.
    }
  double scale = (sin (x) / x) / j[0];	// scale the result
  return (j[n] * scale);
}


//------------------------------------------------------------------

// function using upward recursion
double
up_recursion (double x, int n)
{
  double term_three = 0.;
  double term_one = (sin (x)) / x;	// start with lowest order
  double term_two = (sin (x) - x * cos (x)) / (x * x);	// next order
  for (int k = 1; k < n; k += 1)	// loop for order of function
    { // recurrence relation
      term_three = ((2.*double(k) + 1.) / x) * term_two - term_one;
      term_one = term_two;
      term_two = term_three;
    }
  return (term_three);
}

//------------------------------------------------------------------

// function to calculate relative error
//double
//Rel_Er ()
