#include "header.h"

// A implémenter : 
// Energie cinétique
// Energie potentielle
// Conservation de l'énergie
// Script pour faire un gif de l'évolution du pendule
// Frottement
// RFK45

int main() {

    Pendule DoublePendule;
    DoublePendule.init("./init");
    DoublePendule.evolution(false, false, false, 1);
    DoublePendule.affichage(true);

}
