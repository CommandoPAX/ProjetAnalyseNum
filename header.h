// Déclaration des fonctions et éléments, penser à implémenter le check pour éviter qu'il soit inclus deux fois

#include <string>

double M1, M2, L1, L2, x10, y10, x20, y20, O10, O20, dx10, dx20, dy10, dy20, dO10, dO20; //Valeurs initiales
double t, x1, x2, y1, y2, dx1, dx2, dy1, dy2, ddx1, ddx2, ddy1, ddy2, O1, O2, dO1, dO2, ddO1, ddO2; //Valeurs évolutives
double h; //Le pas de temps
double g; //La gravité de vos actes ne sera pas ignoré

class Pendule{
    private :

    public :
        void init(string);
        void evolution();
        double f1(double, double, double);
        double f2(double, double, double);
};