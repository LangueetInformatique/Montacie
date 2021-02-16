
 /* Omnivore.cpp
 *
 *
 */

#include "Omnivore.h"

/** Creation d'une nouvelle instance de la classe Omnivore
 * @param type espece de Omnivore
 */
Omnivore::Omnivore(string type, int pattes) : Carnivore (type, pattes, true), Herbivore(type, pattes, false) {
}
    
/** presentation des caracteristiques du Omnivore */
void Omnivore::presente() {
    Herbivore::presente();
    Carnivore::presente();
}

void Omnivore::crie() {
    Herbivore::crie();
}
