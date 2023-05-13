set xlabel "x"
set ylabel "y"
set auto x
set auto y
set datafile separator " "
set style line 1 lt 1 linecolor rgb "blue" lw 10 pt 1
set style line 2 lt 1 linecolor rgb "red" lw 10 pt 1
set terminal png
set output "Evolution.png"
plot "./Evol.dat" using 10:6 ls 1 title "M1", "./Evol.dat" using 12:8 ls 2 title "M2"
pause -1
