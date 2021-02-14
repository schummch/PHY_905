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
// To do :
//
//*************************************************************************


//include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
using namespace std; //we need this when.h is omitted

// Function to return sum of
// 1/1 + 1/2 + 1/3 + ..+ 1/n
class gfg
{

public : float sum(int n)
{
    float i, s = 0.0;
    for (i = 1; i <= n; i++)
    s = s + 1/i;
    return s;
}


};

// Driver code
int main()
{
    gfg g;
    int n;
    cout <<"Choose n= ";
    cin>>n;
    cout << "Sum up is " << g.sum(n);
    return 0;
}
