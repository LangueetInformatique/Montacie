/*
 * Herbivore.cpp
 *
 * Created on 16 mars 2006, 19:12
 */

#include "Herbivore.h"

/** Création d'une nouvelle instance de la classe Herbivore
 * @param type espèce de Herbivore
 */
Herbivore::Herbivore(string type, int pattes, bool r) : Animal (type, pattes) {
	ruminant = r;
}
    
/** présentation des caractéristiques de l'herbivore */
void Herbivore::presente() {
	Animal::presente();
    cout << "j'aime les légumes";
    if (ruminant == true) cout << " et je rumine";
    else cout << " et je ne rumine pas"; 
    cout << endl;    
}
