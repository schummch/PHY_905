#  file: derivative_test_905.plt
#
#  Gnuplot plot file for derivative_test_905 output files
#
#  Programmer1:  Dick Furnstahl  furnstahl.1@osu.edu
#  Programmer2:  Chrissy Schumm schummch@msu.edu
#
#  Revision history
#   2021  Created to plot derivative_test_905

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Derivative methods error plot for c++'
set xlabel 'log(h)'
set ylabel 'Error'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-10:0]
# set yrange [-12:-2]

# set the terminal type to be the screen (which is x11 here)
#set term x11

# plot the data as well as the fit, with appropriate titles
plot "derivative_test_905.dat" using ($1):($2) title 'Error for forward difference', \
     "derivative_test_905.dat" using ($1):($3) title 'Error for central difference', \
     "derivative_test_905.dat" using ($1):($4) title 'Error for extrapolated difference'


# output the plot to the file derivative_test_905.ps
set out "derivative_test_905.ps"
set term postscript color enhanced
replot
