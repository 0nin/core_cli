#!/usr/bin/gnuplot -persist

set grid

set term wxt 0
plot 'cable.dat' using 3:4
replot 'cable.dat' using 1:2 title 'DUT 1' with lines


set term wxt 1
plot 'cable.dat' using 7:8
replot 'cable.dat' using 5:6 title 'DUT 2' with lines


set term wxt 2
plot 'cable.dat' using 11:12
replot 'cable.dat' using 9:10 title 'DUT 3' with lines


set term wxt 3
plot 'cable.dat' using 15:16
replot 'cable.dat' using 13:14 title 'DUT 4' with lines

# pause -1
