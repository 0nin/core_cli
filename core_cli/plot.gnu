#!/usr/bin/gnuplot -persist

set grid

set term wxt 0
plot 'cable.dat' using 1:3 title 'DIFF' with points
replot 'cable.dat' using 1:2 title 'DUT 1' with lines


set term wxt 1
plot 'cable.dat' using 1:5 title 'DIFF' with points
replot 'cable.dat' using 1:4 title 'DUT 2' with lines


set term wxt 2
plot 'cable.dat' using 1:7 title 'DIFF' with points
replot 'cable.dat' using 1:6 title 'DUT 3' with lines


set term wxt 3
plot 'cable.dat' using 1:9 title 'DIFF' with points
replot 'cable.dat' using 1:8 title 'DUT 4' with lines

# pause -1
