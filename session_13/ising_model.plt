# file: ising_model.plt
#
# gnuplot plotfile for Monte Carlo sampling test
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history
#   2004-05-09  original version for 780.20 session 22
#   2005-02-22  minor revisions for 780.20 session 12
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title "Energy Distributions"
set xlabel "time"
set ylabel "Energy"

# set the terminal type to be the screen (which is x11 here)
# set term x11

# plot
set style data linespoints
set pointsize 2
plot \
     "ising_model.dat" using 1:2 title 'kT=1' , \
     "ising_model_kT2.0.dat" using 1:2 title 'kT=2.0', \
     "ising_model_kT0.5.dat" using 1:2 title 'kT=0.5.'


# output the plot to the file sampling_test_plt.ps
set out "ising_model_plt.ps"
set term postscript color
replot

reset
set term x11
