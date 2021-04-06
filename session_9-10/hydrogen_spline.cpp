//  file: gsl_spline_test_class.cpp
//
//  Test program for the gsl spline routines using the Spline class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/10/09 -- created from gsl_cubic_spline_test.cpp
//
//  Notes:
//   * uses the GSL interpolation functions (see online documentation)
//
//*****************************************************************
// include files
#include <iostream>    // cout and cin
#include <iomanip>     // manipulators like setprecision
#include <fstream>    // for output file
#include <cmath>
#include <string>     // C++ strings
using namespace std;
#include "GslSpline.h"  // Header file for the GSL Spline class


// function prototypes
inline double H_ur (double x) {return 2*x*exp(-x);} // inline for Breit-Wigner

int
main (void)
{

  // Output file stream
  ofstream hydrogen_spline_out ("hydrogen_spline.dat");

  hydrogen_spline_out << "r       u(r)      u(r)_spline"
                  << endl;

 int npts = 10000;
 int rmin = 1.;
 int rmax = 4.;

 double x_vals[npts];
 double y_vals[npts];

 for (double i=0.; i < npts; i++)
 {
   double x = rmin + i*(rmax - rmin)/(npts - 1);
   x_vals[int(i)] = x;
   y_vals[int(i)] = H_ur(x);
 }

  // Make the spline objects
  string type_cube = "cubic";
  Spline my_spline (x_vals, y_vals, npts, type_cube);


  double r;
  cout << "Choose r value: ";
  cin >> r;

  double y = my_spline.y (r);
  double y_deriv = my_spline.yp (r);
  double y_deriv2 = my_spline.ypp (r);

  hydrogen_spline_out << setprecision(10)
    << r << "     "
    << H_ur (r) << "      "
    << y << "      "
    << y_deriv << "       "
    << y_deriv2 << "      "
    << endl;

  hydrogen_spline_out.close();

  cout << "data stored in hydrogen_spline.dat\n";  //data storage was successful

  return (0);      // successful completion
}
