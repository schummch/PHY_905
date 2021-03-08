# plot file for diffeq_test_exp_back
set timestamp

set xlabel 'log10(t)'
set ylabel 'log10(Rel Error)'

set title 'Comparing Differential Equation Algorithms'
set xrange [.01:.1]

##fit f(x) "diffeq_test.dat" using (log10($1)):(log10(abs(($2-$4)/($4)))) via m, b
##slope_title = sprintf("slope = %-+4.1f",m)

##g(x) = a*x + c
##fit g(x) "diffeq_test.dat" using (log10($1)):(log10(abs(($3-$4)/($4)))) via a, c
##slope_title = sprintf("slope = %-+4.1g",a)

set logscale
plot \
 "diffeq_test.dat" using (($1)):((abs(($2-$4)/($4)))) title 'RelE Eul', \
 "diffeq_test.dat" using (($1)):((abs(($3-$4)/($4)))) title 'RelE R-K'
