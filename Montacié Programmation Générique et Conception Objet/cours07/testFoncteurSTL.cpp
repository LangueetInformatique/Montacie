#include <iostream>
#include "../Cours 03/Complexe.h"

#include <functional>
using namespace std;

template <class T, class F>
T applique(T i, T j, F foncteur) {
    // Applique l'opérateur fonctionnel au foncteur
    // avec comme arguments les deux premiers paramètres :
    return foncteur(i, j);
}

int main(void) {
   
    Complexe Clx1(0.2, -0.54) , Clx2 (0.4, 0.92);
    
    // Utilisation du foncteur "plus" pour faire faire une addition
    // à la fonction "applique" :
    cout << applique(Clx1, Clx2, plus <Complexe>()) << endl;
    return 0;
}
