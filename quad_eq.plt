# gnuplot plot file: quad_eq.plt
set terminal x11   # terminal type (try: help set terminal)
set title ’Landau/Paez 3.4-1 Quadratic Equation’
set xlabel ’c=10^{-n} for n=1..7 [a=1,b=2]’
set ylabel ’relative error’
set logscale
set xrange [1:1e7]
set pointsize 1.5
set key top left
set timestamp
plot "quadratic_eq.dat" using 1:2 title ’1st root’,\
     "quadratic_eq.dat" using 1:3 title ’2nd root’
set out "quadratic_eq.ps"   # name of the output postscript file
set terminal postscript     # switch to postscript mode
replot         # plot to the file
