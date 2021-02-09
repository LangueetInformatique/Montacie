
 /* Omnivore.cpp
 *
 * Created on 16 mars 2006, 19:12
 */

#include "Omnivore.h"

/** Création d'une nouvelle instance de la classe Omnivore
 * @param type espèce de Omnivore
 */
Omnivore::Omnivore(string type, int pattes) : Carnivore (type, pattes, true), Herbivore(type, pattes, false) {
}
    
/** présentation des caractéristiques du Omnivore */
void Omnivore::presente() {
    Herbivore::presente();
    Carnivore::presente();
}

void Omnivore::crie() {
    Herbivore::crie();
}
