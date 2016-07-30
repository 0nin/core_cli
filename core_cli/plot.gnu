#!/usr/bin/gnuplot -persist

set grid

set term x11 0
plot 'diff2.dat' using 1:2
replot 'plot.dat' using 1:2 title 'DUT 1'


set term x11 1
plot 'diff3.dat' using 1:2
replot 'plot.dat' using 1:3 title 'DUT 2'


set term x11 2
plot 'diff4.dat' using 1:2
replot 'plot.dat' using 1:4 title 'DUT 3'


set term x11 3
plot 'diff5.dat' using 1:2
replot 'plot.dat' using 1:5 title 'DUT 4'

# pause -1
