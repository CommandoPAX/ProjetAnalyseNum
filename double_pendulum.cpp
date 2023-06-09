
#include "double_pendulum.h"

using namespace std;
 
void D_Pendulum::init(string path){ //Initialize the pendulum simulation
 
    ifstream init_file(path, ios::in);  // we open the file in read mode
 
    if(init_file)  // if the opening is succesful 
    {       
        init_file >> M1 >> M2 >> L1 >> L2 >> Th1 >> Th2 >> dTh1 >> dTh2;
        cout << "L1 : "<<L1<<" / L2 : "<<L2<< "/ M1 : "<<M1<<" / M2 : "<<M2<< " / Th1 : "<<Th1<<" / Th2 : "<<Th2<< "/ dTh1 : "<<dTh1<<" / Th2 : "<<dTh2<<endl;
        init_file.close();
        // Avoiding the M1/L1 = 0 case, switch P1 and P2
        if(M1==0 || L1==0){
            M1      =   M2;
            L1      =   L2;
            M2      =   0;
            L2      =   0;
            Th1     =   Th2;
            dTh1    =   dTh2;
            Th2     =   0;
            dTh2    =   0;
        }
    }
    else  // If the file cannot be opened
        cerr << "Error : unable to access file" << endl;;
}
    
double D_Pendulum::f_dTh1(double Th1, double Th2, double dTh1, double dTh2){
    double num = -g*(2*M1+M2)*sin(Th1)-M2*g*sin(Th1-2*Th2)-2.0*sin(Th1-Th2)*M2*(pow(dTh2,2)*L2+pow(dTh1,2)*L1*cos(Th1-Th2)); //Equation for the motion of the first mass
    double denom = L1*(2*M1+M2-M2*cos(2*Th1-2*Th2));
    if (denom != 0){
        return (num/denom);
    }
    else {
        return 0;
    }
}
  
double D_Pendulum::f_dTh2(double Th1, double Th2, double dTh1, double dTh2){
      double num        = 2.0*sin(Th1-Th2)*(pow(dTh1,2)*L1*(M1+M2) + g*(M1+M2)*cos(Th1) + pow(dTh2,2)*L2*M2*cos(Th1-Th2)); //Equation for the motion of the second mass
      double denom      = L2*(2.0*M1+M2-M2*cos(2.0*Th1-2.0*Th2));
      if (denom != 0 & M2 != 0){
        return (num/denom);
      }
      else {
        return 0;
      }
}


void D_Pendulum::evolution(double iter, double dt_param, int isdTh1cst, int isdTh2cst) {

    int output_filter = 1;

    dt = dt_param;

    ofstream output_file(DAT_FILENAME, ios::out);  // ouverture en écriture avec effacement du fichier ouvert
    
    for(double t=0; t<=iter; t+=dt) { //Calculates the next step using the RK4 method
        k1X1  =     f_dTh1(Th1,Th2,dTh1,dTh2);
        k1X2  =     dTh1;
        k1dX1 =     f_dTh2(Th1,Th2,dTh1,dTh2);
        k1dX2 =     dTh2;

        k2X1  =     f_dTh1((Th1+k1X2*dt/2),(Th2+k1dX2*dt/2),(dTh1+k1X1*dt/2),(dTh2+k1dX1*dt/2));
        k2X2  =     (dTh1+k1X1*dt/2);
        k2dX1 =     f_dTh2((Th1+k1X2*dt/2),(Th2+k1dX2*dt/2),(dTh1+k1X1*dt/2),(dTh2+k1dX1*dt/2));
        k2dX2 =     (dTh2+k1dX1*dt/2);

        k3X1  =     f_dTh1((Th1+k2X2*dt/2),(Th2+k2dX2*dt/2),(dTh1+k2X1*dt/2),(dTh2+k2dX1*dt/2));
        k3X2  =     (dTh1+k2X1*dt/2); 
        k3dX1 =     f_dTh2((Th1+k2X2*dt/2),(Th2+k2dX2*dt/2),(dTh1+k2X1*dt/2),(dTh2+k2dX1*dt/2));
        k3dX2 =     (dTh2+k2dX1*dt/2);

        k4X1  =     f_dTh1((Th1+k3X2*dt),(Th2+k3dX2*dt),(dTh1+k3X1*dt),(dTh2+k3dX1*dt));
        k4X2  =     (dTh1+k3X1*dt);
        k4dX1 =     f_dTh2((Th1+k3X2*dt),(Th2+k3dX2*dt),(dTh1+k3X1*dt),(dTh2+k3dX1*dt));
        k4dX2 =     (dTh2+k3dX1*dt);

        if(isdTh1cst == 0){
            dTh1 = dTh1+(k1X1+k2X1*2+k3X1*2+k4X1)/6.0*dt;
        }
        Th1 = Th1+(k1X2+k2X2*2+k3X2*2+k4X2)/6.0*dt;

        if(isdTh2cst == 0){
            dTh2 = dTh2+(k1dX1+k2dX1*2+k3dX1*2+k4dX1)/6.0*dt;
        }
        Th2 = Th2+(k1dX2+k2dX2*2+k3dX2*2+k4dX2)/6.0*dt;

        x1 = L1*sin(Th1);
        x2 = x1+L2*sin(Th2);
        y1 = -L1*cos(Th1);
        y2 = y1-L2*cos(Th2);

        dx1 = L1 * dTh1 * cos(Th1 * PI / 180);
        dx2 = dx1 + L2*dTh2*cos(Th2 * PI/180);
        dy1 = L1*dTh1*sin(Th1 * PI/180);
        dy2 = dy1 + L2*dTh2*sin(Th2 * PI/180); 

        Ec1 = (0.5) * M1 * (pow(dx1,2)+ pow(dy1,2));
        Ep1 = M1 * g * y1;
        E1 = Ec1 + Ep1;
        Ec2 = (0.5) * M2 * (pow(dx2,2) + pow(dy2,2));
        Ep2 = M2 * g * y2;
        E2 = Ec2 + Ep2;

        Ec = Ec1 + Ec2;
        Ep = Ep1 + Ep2;
        E  = E1 + E2;

        if(t!=0) {
            output_file << t << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << Th1 << " " << Th2 << " " << dTh1 << " " << dTh2 << " " << Ec << " " << Ep << " " << E << endl; //<< Ec1 << "\t" <<  Ep1 << "\t" << E1 << "\t" << Ec2 << "\t" << Ep2 << "\t" << E2 << endl;
        //Index for the different values
        //t = 1, x1 = 2, y1 = 3, x2 = 4, y2 = 5, Th1 = 6, Th2 = 7, dTh1 = 8, dTh2 = 9, Ec = 10, Ep = 11, E = 12
        }
    }
}

void D_Pendulum::affichage(){ //cette fonction execute le script gnuplot pour faire un graphe

    system("gnuplot D_PendulumXY.plt"); //show the graph for X and Y
    system("gnuplot D_PendulumPhase.plt"); //show the phase diagram
    system("gnuplot D_PendulumE.plt"); //show the energy as a function of time
    system("gnuplot plot.plt");
}
