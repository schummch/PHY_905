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

inline double sqr (double z) {return z*z;}  // inline function for z^2

inline double b_w (double x) {return 63900. / (sqr(x-78.)+sqr(55.)/4.);} // inline for Breit-Wigner

int
main (void)
{

  // Output file stream
  ofstream spline_test_out ("spline_test_poly.dat");

  spline_test_out << "x       y     y_spline      y'_spline     y''_spline"
                  << endl;

  double x_vals[9] = {0., 25., 50., 75., 100., 125., 150., 175., 200.};
  double y_vals[9] = {9.34, 17.9, 41.5, 83.5, 51.5, 21.5, 10.8, 6.29, 4.09};

  int npts = 9.;

  // Make the spline objects
  string type_lin = "linear";
  string type_poly = "polynomial";
  string type_cube = "cubic";
  Spline my_spline (x_vals, y_vals, npts, type_poly);


  // Loop through theoretical points (linear)
  for (int x= 0.; x <= 200; x = x+5)
  {
    double y = my_spline.y (x);
    double y_deriv = my_spline.yp (x);
    double y_deriv2 = my_spline.ypp (x);


    spline_test_out << setprecision(5)
    << x << "     "
    << b_w(x) << "      "
    << y << "      "
    << y_deriv << "       "
    << y_deriv2 << "      "
    << endl;
  }
  spline_test_out.close();

  cout << "data stored in spline_test_poly.dat\n";  //data storage was successful

  return (0);      // successful completion
}
