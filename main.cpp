#include "double_pendulum.h"
//#include "test.h"
#include <iostream>


using namespace std;

// A implémenter : 
// Energie cinétique
// Energie potentielle
// Conservation de l'énergie
// Script pour faire un gif de l'évolution du pendule
// Frottement
// RFK45

int main(int argc, char* argv[]) {

    double iter    = DEFAULT_ITER;
    double dt      = DEFAULT_DT;

    // Reading iteration parameters from command line to avoid recompiling
    if (argc == 1) {
        cout << "Usage : pendulum #iterations #time-step" << endl;
    }
    if (argc > 1) {
        iter    = stod(argv[1]);    // First parameter : number of iterations
        dt      = stod(argv[2]);    // Second parameter : timestep per iteration
    }
    cout << "### Running with iterations : " << iter << " time_step : " << dt << endl;

    D_Pendulum DoublePendule;
    // Init pendulum from init file
    DoublePendule.init("./init");
    // Run pendulum
    DoublePendule.evolution(iter, dt, false, 1, 1, 1);
    // Show pendulum to the world
    DoublePendule.affichage(true);
    return 0;
}
