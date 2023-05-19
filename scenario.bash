#! /usr/bin/bash
#
# Usage : scenario.basch <iterations> <time interval> <Is Th1 constant ? True (1), False (0)>  <Is Th2 constant ? True (1), False (0)> <pendulum init params>
#
# Description : simulation of the double pendulum with RK4 method
#


MULTI_INIT_FILE="./multi_init"
INIT_FILE="./init_temp"
N=0

ITER=$1
DT=$2
TH1CST=$3
TH2CST=$4
cd ./DATA
rm *
cd ../GRAPHES
rm *
cd ../
rmdir ./GRAPHES
rmdir ./DATA
mkdir ./GRAPHES
mkdir ./DATA

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
            ./d_pendulum $ITER $DT $TH1CST $TH2CST $INIT_FILE
            # Saving generate results
            mv ./D_PendulumE.png ./GRAPHES/D_PendulumE_$N.png
            mv ./D_PendulumPhase.png ./GRAPHES/D_PendulumPhase_$N.png
            mv ./D_PendulumXY.png ./GRAPHES/D_PendulumXY_$N.png
            mv ./D_Pendulum.dat ./DATA/D_Pendulum_$N.dat
            ((N=N+1))
        fi
    done < "$MULTI_INIT_FILE"
else
    echo "Error : " $MULTI_INIT_FILE " not found"
fi
