#include "double_pendulum.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    double iter    = DEFAULT_ITER;
    double dt      = DEFAULT_DT;
    double dTh1cst = 0;
    double dTh2cst = 0;
    string init_file;

    // Reading iteration parameters from command line to avoid recompiling
    if (argc == 1 || argc == 2) {
        cout << "Usage : pendulum #iterations #time-step" << endl;
        return 1;
    }
    if (argc == 3) {
        iter    = stod(argv[1]);    // First parameter : number of iterations
        dt      = stod(argv[2]);    // Second parameter : timestep per iteration
        init_file = "./init";
    }
    if (argc == 4) {
        iter        = stod(argv[1]);    // First parameter : number of iterations
        dt          = stod(argv[2]);    // Second parameter : timestep per iteration
        init_file   = argv[3];         // Last optional parameter is for init file selection
    }
    if (argc == 6){
        iter        = stod(argv[1]);    // First parameter : number of iterations
        dt          = stod(argv[2]);    // Second parameter : timestep per iteration
        init_file   = argv[5];         // Last optional parameter is for init file selection
        dTh1cst = stod(argv[3]);    // Third parameter : if dTh1 is constant
        dTh2cst = stod(argv[4]);    // Fourth parameter : if dTh2 is constant
    }
    cout << "# Running with iterations : " << iter << " time_step : " << dt << endl;

    D_Pendulum DoublePendule;
    
    // Init pendulum from init file
    DoublePendule.init(init_file);
    
    // Run pendulum
    DoublePendule.evolution(iter, dt, dTh1cst, dTh2cst);
    
    // Show pendulum to the world
    DoublePendule.affichage();
    return 0;
}
