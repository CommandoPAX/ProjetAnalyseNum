// Déclaration des fonctions et éléments, penser à implémenter le check pour éviter qu'il soit inclus deux fois

#include <string>

// Added default iteration parameters for command line
#define DEFAULT_ITER    100
#define DEFAULT_DT      0.1
#define PI 3.14159265

class Pendule{
    private :
        double M1, M2, L1, L2, x10, y10, x20, y20, O10, O20, dx10, dx20, dy10, dy20, dO10, dO20;                //Valeurs initiales
        double t=0, x1, x2, y1, y2, dx1, dx2, dy1, dy2, ddx1, ddx2, ddy1, ddy2, O1, O2, dO1, dO2, ddO1, ddO2;   //Valeurs évolutives
        double deg = PI / 180;
        double k11=0, k21=0, k31=0, k41=0;
        double k12=0, k22=0, k32=0, k42=0;
        double h = DEFAULT_DT; //Le pas de temps, en seconde normalement
        const double g = 9.81; //La gravité de vos actes ne sera pas ignoré
        double Ec1, Ep1, Ec2, Ep2, E1, E2;
        
        bool showgraph = false; //Bool pour savoir si le programme doit plot un graphe après son execution
        bool frott = false; //Check si on utilise la version avec frottement
        bool frottement = false;
        bool death = false;

        int algo;

        double f1(double, double, double, bool);
        double f2(double, double, double, bool);

    public :
        void init(std::string path);
        void evolution(double, double, int, int, int, int);
        void affichage(bool);
};