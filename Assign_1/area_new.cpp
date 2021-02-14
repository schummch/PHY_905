//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer 1:  Dick Furnstahl  furnstahl.1@osu.edu
//  Programer 2: Christina Schumm   schummch@msu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//      12-Feb-2020  Activity 1 updates from "To do" section
//
//  Notes:
//   * compile with:  "g++ -o area_new.x area_new.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits) DONE
//   2. use a "predefined" value of pi or generate it with atan DONE
//   3. define an inline square function DONE
//   4. split the calculation off into a function (subroutine) DONE
//   5. output to a file (and/or input from a file) DONE
//   6. add checks of the input (e.g., for non-positive radii) DONE
//   7. rewrite using a Circle class
//
//*********************************************************************//

// include files
#include <iostream>	     // this has the cout, cin definitions
#include <iomanip>       // For precision
#include <math.h>      // needed for Pi
#include <fstream>		// note that .h is omitted
using namespace std;     // if omitted, then need std::cout, std::cin

//*********************************************************************//

const double pi = M_PI;   // define pi as a constant

inline double circ_area(double r)
{
  double area = pi * r * r;
  return area;
}

int main ()
{
  double radius;    // every variable is declared as int or double or ...

  // open an output file stream
  ofstream my_out ("area_new.dat");

  my_out << "# Area of a circle"
         << endl;
  do
  {
    cout << "Enter a positive radius of a circle: ";	// ask for radius
    cin >> radius;
  }
  while(radius <= 0);

  if (circ_area(1) != M_PI)
  {
    cout << "Check area calculation" << endl;
    return (0);
  }
  my_out << "radius = "<< radius << endl;
  my_out << "area = " << fixed << setprecision(10) << circ_area(radius) << endl;

  cout << "data stored in area_new.dat." << endl;
  cout << "area: " << circ_area(radius) << endl;

  // close the output file
  my_out.close ();
  return 0;			// "0" for successful completion
}

//------------------------end of main program-----------------------

// function for area of a circle
