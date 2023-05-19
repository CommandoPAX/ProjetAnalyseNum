set xlabel "t"
set ylabel "E"
set auto x
set auto y
set datafile separator "\t"
set style line 1 lt 1 linecolor rgb "blue" lw 1 pt 1
set style line 2 lt 1 linecolor rgb "red" lw 1 pt 1
set style line 3 lt 1 linecolor rgb "green" lw 1 pt 1
set terminal png
set output "D_PendulumE.png"
plot "./D_Pendulum.dat" using 1:10 ls 1 title "Ec", "./D_Pendulum.dat" using 1:11 ls 2 title "Ep", "./D_Pendulum.dat" using 1:12 ls 2 title "E"
