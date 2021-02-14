// ************************************************************************
//file: sum_up_down.cpp
//
//  Program to sum 1/N in two ways
//
//  Programmer: Christina Schumm schummch@msu.edu
//
// Revision history:
//    02 / 12 / 21 created
//
// Notes:
// *An example to try to understand summing upward vs.summing
// downward.Add a small number eps(slightly below single - precision
// machine precision) many times	to	1. It makes a big difference
// (in single precision) whether you do 1 +		eps +	eps +...or
//		eps +	eps +...+ 1.
//
//
//  * First pass:no subroutine
//  * Use single precision AND double precision at the same time
//  * Here is the output with eps = 5e-8 added 10 ^ 7 time:
//
// 1 + eps + eps +...eps + eps +...+ 1
// single precision:1.0000000000 1.5323836803
// double precision:1.4999999992 1.4999999999
//
// Interpretation of Data:
//  According to my data file, there are certain parts where the Relative
// average is equal to zero, and the log becomes infinity. But there does not seem
// to be a pattern, or anything extractable. As N increases, the calculations
// of up vs down vary substantially. After N becomes larger than 264, we do not
// see any more close answers for up and down summations. Summing down works
// better for this situation because when N starts large 1/N and 1/(N-1) are closer
// in magnitude and slowly build in a way that single precision can handle. When
// 1/1 and 1/2 .... are added, there is a bigger conversion jump that has to
// be made that floats lose the precision.
//
//*************************************************************************


//include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>    // for output file
#include <cmath>
using namespace std; //we need this when.h is omitted

// Function to return sum of
// 1/1 + 1/2 + 1/3 + ..+ 1/n
class gfg
{

public : float sum_up(int n) // set single precision integers
{
    float i, s_up = 0.0;
    for (i = 1; i <= n; i++)  // sum from 1 to n
    s_up = s_up + 1/i;    // Summation equation
    return s_up;
}

public : float sum_down(int n) // set single precision integers
{
    float i, s_down = 0.0;
    for (i = n; i >= 1; i--) // sum from n to 1
    s_down = 1./i + s_down;  // summation equation
    return s_down;
}


};

// Driver code
int main()
{
    // open the plot file fstream
    ofstream fplot ("sum_up_down.dat");

    // print out title to screen
    cout << "Relative difference calculation of sum up and down"
      << endl << endl;

    // print titles to the plot file, with "#" as a comment character
    fplot << "# Sum up vs down"
      << endl << endl;
    fplot << "#     n           log10(n)            relative error" << endl;

    // find the magnitude of the relative difference

    gfg g;
    int n =1000;
    // This way is less efficient since I am recalaculting terms in the sum
    // over each loop. But, it is easier to code.
    for (int i = 1; i<= n; i++)
    {
      float num = fabs(g.sum_up(i) - g.sum_down(i));
      float denom = 1./2. * (fabs(g.sum_up(i))+fabs(g.sum_down(i)));

      float rel_error = (num / denom);

      // cout << "Sum up is " << fixed << setprecision(12) << g.sum_up(i) << endl;
      // cout << "Sum down is " << fixed << setprecision(12) << g.sum_down(i) << endl
      //   <<endl;

        // cout << "Relative Error: " << scientific << rel_error << endl;

        // print the relative errors and 1/(a*c) to the plot file
        fplot << "      " << i <<"       "<< scientific << setprecision(15)
          << log10(i) << "       " << log10(rel_error)
          << endl;

    }
    return 0;
}
