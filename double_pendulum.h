#ifndef __STD_LIB__
    #include<iostream>
    #include<cmath>
    #include<time.h>
    #include<stdlib.h>
    #include<fstream>
    #include <iomanip>
    #define __STD_LIB__
#endif

using namespace std;

// Added default iteration parameters for command line
#define DEFAULT_ITER    100
#define DEFAULT_DT      0.1
#define PI              3.14159265
#define DAT_FILENAME    "D_Pendulum.dat"
#define PNG_FILENAME    "D_Pendulum.png"

class D_Pendulum{
    private :
        double M1 = 0;
        double M2 = 0; 
        double L1 = 0;
        double L2 = 0;
        double x1, x2, y1, y2;        // Positions
        double dx1, dx2, dy1, dy2;    // Linear speed
        double Th1, Th2, dTh1, dTh2;  // Angular position, speed, acceleration
        const double DEG = PI/180; //used in the sin and cos function
        double h = DEFAULT_DT;
        const double g = 9.81;
        double Ec1, Ep1, Ec2, Ep2, E1, E2;
        double Ec, Ep, E;

        double t=0, dt;
        double k1X1, k1X2, k1dX1, k1dX2; //RK4 coefficient
        double k2X1, k2X2, k2dX1, k2dX2;
        double k3X1, k3X2, k3dX1, k3dX2;
        double k4X1, k4X2, k4dX1, k4dX2;

        double f_dTh1(double, double, double, double);
        double f_dTh2(double, double, double, double);

    public :
        void init(std::string path);
        void evolution(double, double, int, int);
        void affichage();
};
