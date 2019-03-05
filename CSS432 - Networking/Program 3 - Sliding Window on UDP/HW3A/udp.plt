set terminal postscript landscape
set nolabel
set xlabel "n% drop 1"
set xrange [0:10]
set ylabel "usec"
set yrange [0:8000000]
set output "udp.ps"
plot "1gbpsa-1.dat" title "1gbps slinding window" with linespoints, 3526480 title "1gbps SlidingWindow" with line
