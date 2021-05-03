## file: derivative_test.py
##
## Program to compare derivative approximation methods
##
## Programmer: Chrissy Schumm schummch@msu.edu
##
## Revision history:
##     04/27/21  Original Code Created by Chrissy
##
## Notes:
##  * Based on the discussion of differentiation in Chap. 8
##     of "Computational Physics" by Landau and Paez.
#*****************************************************************
import numpy as np
import matplotlib.pyplot as plt

# define 3 derivative methods at the top, so h can be easily found and changed
def forward_diff(f,a,method='forward',h=10**-7.92):
    if method == 'forward':
        return (f(a + h) - f(a))/(h)

def central_diff(f,a,method='central',h=10**-4.91):
    if method == 'central':
        return (f(a + h/2) - f(a - h/2))/(h)

def extrap_diff(f,a,method='extrapolated',h= 10**-2.51):
    if method == 'extrapolated':
        return ( 8*(f(a + h/4) - f(a - h/4)) - (f(a + h/2) - f(a - h/2)) ) / (3*h)

#************************** main program ***************************

x = np.linspace(0,20,50) # use 50 evenly distributed x-values between 0 and 20
f = lambda x: np.exp(-x) # This is our test function : e^-x (same one we used in class)
y = f(x)

fdydx = forward_diff(f,x)   #find derivative of e^-x using forward difference method
cdydx = central_diff(f, x)  #find derivative of e^-x using central difference method
edydx = extrap_diff(f, x)   #find derivative of e^-x using extrapolated difference method

exact = -np.exp(-x)  #This is our exact value of the derivative we will use for comparison

#************************** Plot the graph ***************************
plt.figure(figsize=(12,5))
plt.plot(x,y,label='y=f(x)')
plt.plot(x,fdydx,'r.', label="Forward Difference y=f'(x)")
plt.plot(x,cdydx,'s', label="Central Difference y=f'(x)")
plt.plot(x,edydx,'p', label="Extrapolated Difference y=f'(x)")
plt.plot(x, exact, 'b', label= 'Exact')
plt.title('Derivative Methods of y= e^-x')
plt.xlabel('x value to take derivative')
plt.ylabel('Derivative Value')
plt.legend()
plt.grid(True)
plt.show()


