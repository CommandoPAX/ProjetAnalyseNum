#include "header.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.14159265

using namespace std;

// On commence par implémenter l'initialisation de la classe
void Pendule::init(string path){ //Cette fonction permet de récupéré les paramètres initiaux du pendules
 
    ifstream fichier(path, ios::in);  // on ouvre le fichier en lecture
 
        if(fichier)  // si l'ouverture a réussi
        {       
             fichier >> M1 >> M2 >> L1 >> L2 >> O1 >> O2 >> dO1 >> dO2; //On envoie les valeurs dans chacune des variables initiales
             // La plupart des valeurs initiales sont sûrement inutiles, je les laisse pour le moment au cas où je m'en sers
             fichier.close();  // on ferme le fichier
        }
        else  // sinon
            cerr << "Impossible d'ouvrir le fichier !" << endl;;
}

double Pendule::f1(double f1t, double f1y, double f1dy, bool frott){ //On définit la fonction f1 pour dd01
// A implémenter : une autre fonction pour la version avec frottement
    DeltaO1 = O2 - f1y ;
    fO11 = f1dy*f1dy*M2*cos(DeltaO1 * PI /180)*sin(DeltaO1 * PI / 180) + dO2*dO2*M2*L2*sin(DeltaO1 * PI / 180) - (M1 + M2)*g*sin(f1y * PI / 180) + M2*cos(DeltaO1 * PI / 180)*g*sin(O2 * PI / 180) ;
    fO12 = (M1 + M2)*L1 - M2*L1*cos(DeltaO1 * PI /180)*cos(DeltaO1 * PI / 180) ;
    if(fO12 != 0){
        fO1 = fO11 / fO12;
        return fO1;
    }
    else{
        return 1;
    }
}

double Pendule::f2(double f2t, double f2y, double f2dy, bool frott){ //On définit la fonction f2 pour dd02
// A implémenter : une autre fonction pour la version avec frottement
    DeltaO2 = f2y - O1;
    fO21 = -f2dy*f2dy*M2*L1*cos(DeltaO2 * PI / 180)*sin(DeltaO2 * PI / 180) + (M1 + M2)*(g*sin(O1 * PI / 180)*cos(DeltaO2 * PI / 180) - L1*dO1*dO1*sin(DeltaO2 * PI / 180) - g*sin(f2y * PI / 180)) ;
    fO22 = (M1 + M2)*L2 - M2*L1*cos(DeltaO2 * PI / 180)*cos(DeltaO2 * PI / 180) ;
    if(fO22 != 0){
        fO2 = fO21 / fO22;
        return fO2;
    }
    else{
        return 1;
    }
}

void Pendule::evolution(bool dO1cst, bool dO2cst, bool frottement, int algo){ //Implémentation de la méthode RK4, c'est la partie fun du projet, le reste sera plus tranquille
    ofstream fichier("Evol.dat", ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert
    //fichier << "t" << " " << "O1" << " " << "dO1" << " " << "O2" << " " << "dO2" << " " << "x1" << " " << "dx1" << " " << "x2" << " " << "dx2" << " " << "y1" << " " << "dy1" << " " << "y2" << " " << "dy2" <<endl;
    for (int i = 0 ; i <=10000; i++){ // 10000 c'est pour pas qu'il tourne à l'infini
        
        x1  = L1*sin(O1 * PI / 180);
        x2  = L1*sin(O1) + L2 * sin(O2 * PI / 180);
        y1 = -L1 * cos(O1 * PI / 180); //De manière random j'ai une erreur sur cette ligne, c'est un prank elle existe pas
        y2 = -L1 * cos(O1) - L2 * cos(O2 * PI / 180);
        dx1 = L1 * dO1 * cos(O1 * PI / 180);
        dx2 = L1*dO1*cos(O1 * PI / 180) + L2*dO2*cos(O2 * PI / 180);
        dy1 = L1*dO1*cos(O1 * PI / 180);
        dy2 = L1*dO1*cos(O1 * PI / 180) - L2*dO2*cos(O2 * PI / 180); 

        if(fichier && i%100==0)
        {
            fichier << t << " " << O1 << " " << dO1 << " " << O2 << " " << dO2 << " " << x1 << " " << dx1 << " " << x2 << " " << dx2 << " " << y1 << " " << dy1 << " " << y2 << " " << dy2 <<endl;
        }

        switch(algo){
            case 1 : // RK4
                t = h * i; //Calcul des coefficients de résolution pour RK4
                k11 = Pendule::f1(t, O1, dO1, frottement);
                k21 = Pendule::f1(t + h/2, 01+(h/2)*dO1, dO1+(h/2)*k11, frottement);
                k31 = Pendule::f1(t + h/2, O1+(h/2)*dO1+(h*h/4)*dO1, dO1+(h/2)*k21, frottement);
                k41 = Pendule::f1(t + h, O1+h*dO1, dO1+h*k31, frottement);

                k12 = Pendule::f2(t, O2, dO2, frottement);
                k22 = Pendule::f2(t + h/2, 02+(h/2)*dO2, dO2+(h/2)*k12, frottement);
                k32 = Pendule::f2(t + h/2, O2+(h/2)*dO2+(h*h/4)*dO2, dO2+(h/2)*k22, frottement);
                k42 = Pendule::f2(t + h, O2+h*dO2, dO2+h*k32, frottement);

                O1 = O1 + h*dO1 + (h*h/6)*(k11 + k21 + k31);
                if(dO1cst == false){ //Vérifie si on impose que la vitesse est constante pour M1
                    dO1 = dO1 + (h/6)*(k11 + 2*k21 + 2*k31 + k41);
                }
                else{
                    dO1 = dO1;
                }

                O2 = O2 + h*dO2 + (h*h/6)*(k12 + k22 + k32);
                if(dO2cst == false){ //Vérifie si on impose que la vitesse est constante pour M2
                    dO2 = dO2 + (h/6)*(k12 + 2*k22 + 2*k32 + k42);
                }
                else{
                    dO2 = dO2;
                }
                break;

            case 2 :
                //Code goes here
                break;

            default :
                cerr << "Algorithme invalide" << endl;
                death = true;
                break;
        }
        //Calcul des coordonnées à partir des relations trigonométriques

        if(death == true){
            break;
        }
    }
    fichier.close();
}

void Pendule::affichage(bool showgraph){ //cette fonction execute le script gnuplot pour faire un graphe
    // A implémenter : espace des phase O1 en fonction de dO1, O2 en fonction de dO2
    if(showgraph == true){
        system("gnuplot plot.plt");
        cout << "Affichage";
    }
}
