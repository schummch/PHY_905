#  file: derivative_test.plt
#
#  Gnuplot plot file for derivative_test output
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Test of Numerical Derivatives using exp(-x)'
set xlabel 'log10(mesh size)'
set ylabel 'relative error'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-10:0]
set yrange [-17:0]

# fit the curve 1
f1(x) = m1*x + b1
fit [-5:-1] f1(x) "derivative_test.dat" using ($1):($3) via m1,b1
fit_title_1 = sprintf("%-+4.1f*x %-+4.1f",m1,b1)

f2(x) = m2*x + b2
fit [-2:-1] f2(x) "derivative_test.dat" using ($1):($4) via m2,b2
fit_title_2 = sprintf("%-+4.1f*x %-+4.1f",m2,b2)

f3(x) = m3*x + b3
fit [-1.8:-.2] f3(x) "derivative_test.dat" using ($1):($5) via m3,b3
fit_title_3 = sprintf("%-+4.1f*x %-+4.1f",m3,b3)

# set the terminal type to be the screen (which is x11 here)
#set term x11

# plot the data as well as the fit, with appropriate titles
plot "derivative_test.dat" using ($1):($3) title 'Cent difference', \
      m1*x + b1 title fit_title_1, \
      "derivative_test.dat" using ($1):($4) title 'Extrap difference', \
      m2*x + b2 title fit_title_2, \
      "derivative_test.dat" using ($1):($5) title 'Extrap2 difference', \
      m3*x + b3 title fit_title_3

# output the plot to the file derivative_test_plt.ps
set out "derivative_test_plt.ps"
set term postscript color enhanced
replot
