#!/usr/bin/gnuplot -persist

set grid
plot 'normalized.dat' using 1:2
replot 'normalized.dat' using 1:3
replot 'normalized.dat' using 1:4
replot 'normalized.dat' using 1:5
