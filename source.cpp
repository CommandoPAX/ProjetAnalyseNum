#include "header.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double g = 9.87;

// On commence par implémenter l'initialisation de la classe
void Pendule::init(string path){
 
    ifstream fichier(path, ios::in);  // on ouvre le fichier en lecture
 
        if(fichier)  // si l'ouverture a réussi
        {       
             fichier >> M1 >> M2 >> L1 >> L2 >> x1 >> x2 >> y1 >> y2 >> O1 >> O2 >> dx1 >> dx2 >> dy1 >> dy2 >> dO1 >> dO2; //On envoie les valeurs dans chacune des variables initiales
             // La plupart des valeurs initiales sont sûrement inutiles, je les laisse pour le moment au cas où je m'en sers
             fichier.close();  // on ferme le fichier
        }
        else  // sinon
            cerr << "Impossible d'ouvrir le fichier !" << endl;;
}

double Pendule::f1(double f1t, double f1y, double f1dy){ //On définit la fonction f1 pour dd01
    double fO1 = (f1dy*f1dy*M2*cos(O2 - f1y)*sin(O2-01) + dO2*dO2*M2*L2*sin(O2-f1y) - (M1 + M2)*g*sin(f1y) + M2*cos(O2-f1y)*g*sin(O2)) / ((M1 + M2)*L1 - M2*L1*cos(O2 - f1y)*cos(O2-f1y)) ;
    return fO1;
}

double Pendule::f2(double f2t, double f2y, double f2dy){ //On définit la fonction f2 pour dd02
    double fO2 = (-f2dy*f2dy*M2*L1*cos(f2y - O1)*sin(f2y - 01) + (M1 + M2)*(g*sin(O1)*cos(f2y-O1) - L1*dO1*dO1*sin(f2y - O1) - g*sin(f2y)))/((M1 + M2)*L2 - M2*L1*cos(f2y-O1)*cos(f2y-O1)) ;
    return fO2;
}

void Pendule::evolution(){ //Implémentation de la méthode RK4, c'est la partie fun du projet, le reste sera plus tranquille
    ofstream fichier("Evol.dat", ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert
    for (int i = 0 ; i <=10000; i++){
        t = h * i;
        double k11 = Pendule::f1(t, O1, dO1);
        double k21 = Pendule::f1(t + h/2, 01+(h/2)*dO1, dO1+(h/2)*k11);
        double k31 = Pendule::f1(t + h/2, O1+(h/2)*dO1+(h*h/4)*dO1, dO1+(h/2)*k21 );
        double k41 = Pendule::f1(t + h, O1+h*dO1, dO1+h*k31);

        double k12 = Pendule::f2(t, O2, dO2);
        double k22 = Pendule::f2(t + h/2, 02+(h/2)*dO2, dO2+(h/2)*k12);
        double k32 = Pendule::f2(t + h/2, O2+(h/2)*dO2+(h*h/4)*dO2, dO2+(h/2)*k22);
        double k42 = Pendule::f2(t + h, O2+h*dO2, dO2+h*k32);

        O1 = O1 + h*dO1 + (h*h/6)*(k11 + k21 + k31);
        dO1 = dO1 + (h/6)*(k11 + 2*k21 + 2*k31 + k41);

        O2 = O2 + h*dO2 + (h*h/6)*(k12 + k22 + k32);
        dO2 = dO2 + (h/6)*(k12 + 2*k22 + 2*k32 + k42);

        //Calcul des coordonnées à partir des relations trigonométriques

        x1  = L1*sin(O1);
        x2  = L1*sin(O1) + L2 * sin(O2);
        y1 = -L1 * cos(O1); //De manière random j'ai une erreur sur cette ligne, c'est un prank elle existe pas
        y2 = -L1 * cos(O1) - L2 * cos(O2);
        dx1 = L1 * dO1 * cos(O1);
        dx2 = L1*dO1*cos(O1) + L2*dO2*cos(O2);
        dy1 = L1*dO1*cos(O1);
        dy2 = L1*dO1*cos(O1) - L2*dO2*cos(O2); 

        if(fichier && i%100==0)
        {
            fichier << t << O1 << dO1 << O2 << dO2 << x1 << dx1 << x2 << dx2 << y1 << dy1 << y2 << dy2 <<endl;
        }
        else
        {
            cerr << "Erreur" << endl;
            break;
        }
    }
    fichier.close();
}