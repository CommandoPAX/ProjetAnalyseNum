set xlabel "Th"
set ylabel "dTh"
set auto x
set auto y
set datafile separator "\t"
set style line 1 lt 1 linecolor rgb "blue" lw 5 pt 1
set style line 2 lt 1 linecolor rgb "red" lw 1 pt 1
set terminal png
set output "D_PendulumPhase.png"
plot "./D_Pendulum.dat" using 6:8 ls 1 title "M1", "./D_Pendulum.dat" using 7:9 ls 2 title "M2"
