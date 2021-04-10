#  file: eigen_basis.plt
#
#  Gnuplot plot file for eigen_basis output files
#
#  Programmer1:  Dick Furnstahl  furnstahl.1@osu.edu
#  Programmer2:  Chrissy Schumm schummch@msu.edu
#
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#   2021  changed to plot eigen_basis

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Various Eigen Vector plots'
set xlabel 'r'
set ylabel 'Eigenvalue'

# move the legend to a free space
set key right

# set the x and y axis scales (already logs)
set xrange [0:15]
# set yrange [-17:0]

# set the terminal type to be the screen (which is x11 here)
#set term x11

# plot the data as well as the fit, with appropriate titles
plot "eigen_basis_dim=1.dat" using ($1):($2) title 'Dimension1', \
     "eigen_basis_dim=5.dat" using ($1):($2) title 'Dimension5', \
     "eigen_basis_dim=10.dat" using ($1):($2) title 'Dimension10', \
     "eigen_basis_dim=20.dat" using ($1):($2) title 'Dimension20'


# output the plot to the file eigen_basis.ps
set out "eigen_basis.ps"
set term postscript color enhanced
replot
