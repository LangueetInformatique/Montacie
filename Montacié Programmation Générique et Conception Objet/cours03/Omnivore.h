#ifndef OMNIVORE_H_
#define OMNIVORE_H_

#endif /*OMNIVORE_H_*/

/*
 * Omnivore.h
 *
 *
 */

#include "Herbivore.h"
#include "Carnivore.h"

/** Creation et gestion d'omnivores
 * @author montacie
 */
class Omnivore : public Herbivore, public Carnivore {
public:
    /** Creation d'une nouvelle instance de la classe Omnivore
     * @param type espece de omnivores
     */
    Omnivore(string type, int pattes);
    
    /** presentation des caracteristiques de l'omnivore */
    void presente();

   /** cri de l'animal */
    void crie();
};
