
 /* Carnivore.cpp
 *
 *
 */

#include "Carnivore.h"

/** Creation d'une nouvelle instance de la classe Carnivore
 * @param type espece de carnivore
 */
Carnivore::Carnivore(string type, int pattes, bool d) : Animal (type, pattes) {
	doux = d;
}
    
/** presentation des caracteristiques du carnivore */
void Carnivore::presente() {
	Animal::presente();
    cout << "j'aime la viande";
    if (doux == false) cout << " et je suis cruel";
    else cout << " et je suis doux"; 
    cout << endl; 
}

