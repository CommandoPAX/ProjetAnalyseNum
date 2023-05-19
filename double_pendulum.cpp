
#include "double_pendulum.h"

using namespace std;
 
void D_Pendulum::init(string path){ //Cette fonction permet de récupéré les paramètres initiaux du pendules
 
    ifstream init_file(path, ios::in);  // on ouvre le fichier en lecture
 
    if(init_file)  // si l'ouverture a réussi
    {       
        init_file >> M1 >> M2 >> L1 >> L2 >> Th1 >> Th2 >> dTh1 >> dTh2; //Thn envoie les valeurs dans chacune des variables initiales
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
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;;
}

double D_Pendulum::f_Th1(double Th1, double Th2, double dTh1, double dTh2) {
      return dTh1;}
    
double D_Pendulum::f_dTh1(double Th1, double Th2, double dTh1, double dTh2){
    double num = -g*(2*M1+M2)*sin(Th1)-M2*g*sin(Th1-2*Th2)-2.0*sin(Th1-Th2)*M2*(pow(dTh2,2)*L2+pow(dTh1,2)*L1*cos(Th1-Th2));
    double denom = L1*(2*M1+M2-M2*cos(2*Th1-2*Th2));
    if (denom != 0){
    return (num/denom);
    }
    else {
        return 0;
    }
}

double D_Pendulum::f_Th2(double Th1, double Th2, double dTh1, double dTh2){
      return dTh2;}
  
double D_Pendulum::f_dTh2(double Th1, double Th2, double dTh1, double dTh2){
      double num        = 2.0*sin(Th1-Th2)*(pow(dTh1,2)*L1*(M1+M2) + g*(M1+M2)*cos(Th1) + pow(dTh2,2)*L2*M2*cos(Th1-Th2));
      double denom      = L2*(2.0*M1+M2-M2*cos(2.0*Th1-2.0*Th2));
      if (denom != 0){
            return (num/denom);
      }
      else {
        return 0;
      }
}


void D_Pendulum::evolution(double iter, double dt_param, int isdTh1cst, int isdTh2cst, int frottement, int algo) {
    double t=0, dt;
    double k1X1, k1X2, k1dX1, k1dX2;
    double k2X1, k2X2, k2dX1, k2dX2;
    double k3X1, k3X2, k3dX1, k3dX2;
    double k4X1, k4X2, k4dX1, k4dX2;
    double x1, x2, y1, y2;

    int output_filter = 1;

    dt = dt_param;

    ofstream output_file(DAT_FILENAME, ios::out);  // ouverture en écriture avec effacement du fichier ouvert
    
    for(double t=0; t<=iter; t+=dt) {         
        k1X1  =     f_dTh1(Th1,Th2,dTh1,dTh2);
        k1X2  =     f_Th1(Th1,Th2,dTh1,dTh2);
        k1dX1 =     f_dTh2(Th1,Th2,dTh1,dTh2);
        k1dX2 =     f_Th2(Th1,Th2,dTh1,dTh2);

        k2X1  =     f_dTh1((Th1+k1X2*dt/2),(Th2+k1dX2*dt/2),(dTh1+k1X1*dt/2),(dTh2+k1dX1*dt/2));
        k2X2  =     f_Th1((Th1+k1X2*dt/2),(Th2+k1dX2*dt/2),(dTh1+k1X1*dt/2),(dTh2+k1dX1*dt/2));
        k2dX1 =     f_dTh2((Th1+k1X2*dt/2),(Th2+k1dX2*dt/2),(dTh1+k1X1*dt/2),(dTh2+k1dX1*dt/2));
        k2dX2 =     f_Th2((Th1+k1X2*dt/2),(Th2+k1dX2*dt/2),(dTh1+k1X1*dt/2),(dTh2+k1dX1*dt/2));

        k3X1  =     f_dTh1((Th1+k2X2*dt/2),(Th2+k2dX2*dt/2),(dTh1+k2X1*dt/2),(dTh2+k2dX1*dt/2));
        k3X2  =     f_Th1((Th1+k2X2*dt/2),(Th2+k2dX2*dt/2),(dTh1+k2X1*dt/2),(dTh2+k2dX1*dt/2)); 
        k3dX1 =     f_dTh2((Th1+k2X2*dt/2),(Th2+k2dX2*dt/2),(dTh1+k2X1*dt/2),(dTh2+k2dX1*dt/2));
        k3dX2 =     f_Th2((Th1+k2X2*dt/2),(Th2+k2dX2*dt/2),(dTh1+k2X1*dt/2),(dTh2+k2dX1*dt/2));

        k4X1  =     f_dTh1((Th1+k3X2*dt),(Th2+k3dX2*dt),(dTh1+k3X1*dt),(dTh2+k3dX1*dt));
        k4X2  =     f_Th1((Th1+k3X2*dt),(Th2+k3dX2*dt),(dTh1+k3X1*dt),(dTh2+k3dX1*dt));
        k4dX1 =     f_dTh2((Th1+k3X2*dt),(Th2+k3dX2*dt),(dTh1+k3X1*dt),(dTh2+k3dX1*dt));
        k4dX2 =     f_Th2((Th1+k3X2*dt),(Th2+k3dX2*dt),(dTh1+k3X1*dt),(dTh2+k3dX1*dt));

        dTh1 = dTh1+(k1X1+k2X1*2+k3X1*2+k4X1)/6.0*dt;
        Th1 = Th1+(k1X2+k2X2*2+k3X2*2+k4X2)/6.0*dt;
        dTh2 = dTh2+(k1dX1+k2dX1*2+k3dX1*2+k4dX1)/6.0*dt;
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
            output_file << t << "\t" << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << "\t" << Th1 << "\t" << Th2 << "\t" << dTh1 << "\t" << dTh2 << "\t" << Ec << "\t" << Ep << "\t" << E << endl; //<< Ec1 << "\t" <<  Ep1 << "\t" << E1 << "\t" << Ec2 << "\t" << Ep2 << "\t" << E2 << endl;
        //t = 1, x1 = 2, y1 = 3, x2 = 4, y2 = 5, Th1 = 6, Th2 = 7, dTh1 = 8, dTh2 = 9, Ec1 = 10, Ep1 = 11, E1 = 12, Ec2 = 13, Ep2 = 14, E2 = 15
        }
    }
}

void D_Pendulum::affichage(){ //cette fonction execute le script gnuplot pour faire un graphe

    system("gnuplot D_PendulumXY.plt");
    system("gnuplot D_PendulumPhase.plt");
    system("gnuplot D_PendulumE.plt");
}