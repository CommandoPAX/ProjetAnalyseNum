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
#define ALGO_1          1
#define ALGO_2          2
#define DAT_FILENAME    "D_Pendulum.dat"
#define PNG_FILENAME    "D_Pendulum.png"

class D_Pendulum{
    private :
        double M1, M2, L1, L2;
        double t=0, x1, x2, y1, y2;                 // Positions
        double dx1, dx2, dy1, dy2;                  // Linear speed
        double ddx1, ddx2, ddy1, ddy2;              // Linear acceleration
        double Th1, Th2, dTh1, dTh2, ddTh1, ddTh2;  // Angular position, speed, acceleration
        const double DEG = PI/180;
        double k1_1=0, k2_1=0, k3_1=0, k4_1=0;
        double k1_2=0, k2_2=0, k3_2=0, k4_2=0;
        double h = DEFAULT_DT; //Le pas de temps, en seconde normalement
        const double g = 9.81; //La gravité de vos actes ne sera pas ignoré
        double Ec1, Ep1, Ec2, Ep2, E1, E2;
        
        bool showgraph = false; //Bool pour savoir si le programme doit plot un graphe après son execution
        bool frott = false; //Check si on utilise la version avec frottement
        bool frottement = false;
        bool death = false;

        int algo;

        double f_Th1(double, double, double, double);
        double f_Th2(double, double, double, double);
        double f_dTh1(double, double, double, double);
        double f_dTh2(double, double, double, double);

    public :
        void init(std::string path);
        void evolution(double, double, int, int, int, int);
        void affichage(bool);
};
