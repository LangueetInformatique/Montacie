/*
 * Herbivore.cpp
 *
 *
 */

#include "Herbivore.h"

/** Creation d'une nouvelle instance de la classe Herbivore
 * @param type espece de Herbivore
 */
Herbivore::Herbivore(string type, int pattes, bool r) : Animal (type, pattes) {
	ruminant = r;
}
    
/** presentation des caracteristiques de l'herbivore */
void Herbivore::presente() {
	Animal::presente();
    cout << "j'aime les legumes";
    if (ruminant == true) cout << " et je rumine";
    else cout << " et je ne rumine pas"; 
    cout << endl;    
}
