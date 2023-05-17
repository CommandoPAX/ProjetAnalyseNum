#! /usr/bin/bash
#
# Usage : scenario.basch <iterations> <time interval> <pendulum init params>
#
# Description : simulation of the double pendulum with RK4 method
#


MULTI_INIT_FILE="./multi_init"
INIT_FILE="./init_temp"
N=0

ITER=$1
DT=$2

if [[ -e $MULTI_INIT_FILE ]]
then
    # Reading parameter file
    while IFS=' ' read -r M1 M2 L1 L2 TH1 TH2 DTH1 DTH2
    do
        FIRST_CHAR=`echo $M1 | awk '{print $1}'`
        if [[ $FIRST_CHAR != "#" ]]
        then
            echo $M1    $M2 $L1 $L2 $TH1    $TH2    $DTH1   $DTH2   > $INIT_FILE
            # Generate double pendulum data
            ./d_pendulum $ITER $DT $INIT_FILE
            # Plotting data
#            gnuplot ./D_Pendulum.dat
            # Saving generate results
            mv ./D_Pendulum.png ./D_Pendulum_$N.png
            mv ./D_Pendulum.dat ./D_Pendulum_$N.dat
            ((N=N+1))
        fi
    done < "$MULTI_INIT_FILE"
else
    echo "Error : " $MULTI_INIT_FILE " not found"
fi

