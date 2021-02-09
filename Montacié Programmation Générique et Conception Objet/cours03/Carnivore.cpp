
 /* Carnivore.cpp
 *
 * Created on 16 mars 2006, 19:12
 */

#include "Carnivore.h"

/** Création d'une nouvelle instance de la classe Carnivore
 * @param type espèce de carnivore
 */
Carnivore::Carnivore(string type, int pattes, bool d) : Animal (type, pattes) {
	doux = d;
}
    
/** présentation des caractéristiques du carnivore */
void Carnivore::presente() {
	Animal::presente();
    cout << "j'aime la viande";
    if (doux == false) cout << " et je suis cruel";
    else cout << " et je suis doux"; 
    cout << endl; 
}

