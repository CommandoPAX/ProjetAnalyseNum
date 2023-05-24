set xlabel "x"
set ylabel "y"
set xrange [-2:2]
set yrange [-2:2]
set datafile separator " "
set style line 1 lt 1 linecolor rgb "blue" lw 5 pt 1
set style line 2 lt 1 linecolor rgb "red" lw 1 pt 1
set terminal png
set output "D_PendulumXY.png"
plot "./D_Pendulum.dat" using 2:3 ls 1 title "M1", "./D_Pendulum.dat" using 4:5 ls 2 title "M2"
