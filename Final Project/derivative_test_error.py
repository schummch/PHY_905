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
    return (( 8*(f(x + h/4) - f(x - h/4)) - (f(x + h/2) - f(x - h/2)) ) / (3*h))


#****************************** Main *********************************
h_min = 10**-10   #Choose minimum step size
x = 1  #Choose to evaluate at x=1

exact = -np.exp(-x) #Calculates the exact derivative at point x, for comparison

#Initialize empty arrays to create error plots
logh_arr=[]
fderr_arr=[]
cderr_arr=[]
ederr_arr=[]

#Create a while loop to compare decreasing step sizes
h=.1
while (h >= h_min):
    diff_fd = forward_diff(x, h, f)
    diff_cd = central_diff(x, h, f)
    diff_ed = extrap_diff(x, h, f)

    logh_arr.append(math.log(h,10))
    fderr_arr.append(math.log(abs((diff_fd-exact)/exact),10))
    cderr_arr.append(math.log(abs((diff_cd-exact)/exact),10))
    ederr_arr.append(math.log(abs((diff_ed-exact)/exact),10))
    
    h/= 2

#************************** Plot the graph ***************************
plt.figure(figsize=(12,5))
plt.plot(logh_arr,fderr_arr,'r.', label="Forward Difference Error")
plt.plot(logh_arr,cderr_arr,'s', label="Central Difference Error")
plt.plot(logh_arr,ederr_arr,'p', label="Extrapolated Difference Error")
plt.title('Derivative Methods Error Plots')
plt.xlabel('log(h)')
plt.ylabel('Error')
plt.legend()
plt.grid(True)
plt.savefig('derivative_test_error.jpg', bbox_inches='tight')
plt.show()
