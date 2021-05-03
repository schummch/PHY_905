# file: derivative_test.py
##
## Program to study the error in differentiation rules
##
## Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
## Programmer 2: Chrissy Schumm schummch@msu.edu
##
## Revision history:
##     01/14/04  original version, translated from derivative_test.c
##     01/14/07  modified to be consistent with derivative_test_simple.cpp
##     04/27/21  modified to work with python
##
## Notes:
##  * Based on the discussion of differentiation in Chap. 8
##     of "Computational Physics" by Landau and Paez.
##  * Use the adaptive gsl_diff_central function as well.
##     Output from this with e^(-x) at x=1 is:
## gsl_diff_central(1) = -3.6787944117560983e-01 +/- 6.208817e-04
##  actual relative error: 1.13284386e-11
#*****************************************************************
import numpy as np
import math
import matplotlib.pyplot as plt

#************************** test_function ***************************

f = lambda x: np.exp(-x)

#********************** test_function_derivative ********************

def test_function_derivative (x):
  return (-np.exp (-x))

#************************* forward_diff ****************************

def forward_diff (x, h, f):
  return (( f(x + h) - f(x) ) / h)

#************************* central_diff *******************************

def central_diff (x, h, f):
    return (( f(x + h/2.) - f(x - h/2.) ) / h)

#************************* extrap_diff *******************************

def extrap_diff(x, h, f):
    return (( 8*(f(x + h/4) - f(x - h/4)) - (f(x + h/2) - f(x - h/2)) ) / (3*h))#************************** test_function ***************************


#****************************** Main *********************************
h_min = 10**-10
print(h_min)
x = 1

exact = -np.exp(-x)
h=.1
while (h >= h_min):
    diff_fd = forward_diff(x, h, f)
    diff_cd = central_diff(x, h, f)
    diff_ed = extrap_diff(x, h, f)

    plt.figure(figsize=(12,5))
    plt.plot(x,diff_fd,'r.', label="Forward Difference Error")
    plt.plot(x, diff_cd,'s', label="Central Difference Error")
    plt.plot(x,diff_ed,'p', label="Extrapolated Difference Error")
    plt.title('Derivative Methods Error Plots')
    plt.xlabel('b value')
    plt.ylabel('Error')
    plt.legend()
    plt.grid(True)

    h/= 2

plt.show()
