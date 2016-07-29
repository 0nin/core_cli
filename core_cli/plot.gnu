#!/usr/bin/gnuplot -persist

set grid
#plot 'normalized.dat' using 1:2
#replot 'normalized.dat' using 1:3
#replot 'normalized.dat' using 1:4
#replot 'normalized.dat' using 1:5

set term wxt 0
plot 'diff2.dat' using 1:2
replot 'plot.dat' using 1:2 title 'DUT 1'


set term wxt 1
plot 'diff3.dat' using 1:2
replot 'plot.dat' using 1:3 title 'DUT 2'


set term wxt 2
plot 'diff4.dat' using 1:2
replot 'plot.dat' using 1:4 title 'DUT 3'


set term wxt 3
plot 'diff5.dat' using 1:2
replot 'plot.dat' using 1:5 title 'DUT 4'
