// Déclaration des fonctions et éléments, penser à implémenter le check pour éviter qu'il soit inclus deux fois

#include <string>

class Pendule{
    private :
        double M1, M2, L1, L2, x10, y10, x20, y20, O10, O20, dx10, dx20, dy10, dy20, dO10, dO20; //Valeurs initiales
        double t, x1, x2, y1, y2, dx1, dx2, dy1, dy2, ddx1, ddx2, ddy1, ddy2, O1, O2, dO1, dO2, ddO1, ddO2; //Valeurs évolutives
        double DeltaO1, fO1, fO11, fO12;
        double DeltaO2, fO2, fO21, fO22;
        double k11, k21, k31, k41;
        double k12, k22, k32, k42;
        double h = 0.001; //Le pas de temps, en seconde normalement
        double g = 9.81; //La gravité de vos actes ne sera pas ignoré
        double Ec1, Ep1, Ec2, Ep2, E1, E2;
        
        bool dO1cst = false, dO2cst = false;
        bool showgraph = false; //Bool pour savoir si le programme doit plot un graphe après son execution
        bool frott = false; //Check si on utilise la version avec frottement
        bool frottement = false;
        bool death = false;

        int algo;

        double f1(double, double, double, bool);
        double f2(double, double, double, bool);

    public :
        void init(std::string path);
        void evolution(bool, bool, bool, int);
        void affichage(bool);
};
