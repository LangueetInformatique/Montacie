#ifndef CARNIVORE_H_
#define CARNIVORE_H_

#endif /*CARNIVORE_H_*/

/*
 * Carnivore.h
 *
 *
 */

#ifndef ANIMAL_H_
#include "Animal.h"
#endif

/** Creation et gestion de carnivores
 * @author montacie
 */
class Carnivore : public Animal {
protected:
    /** est-ce un animal doux ? */    
    bool doux;
public:
    /** Creation d'une nouvelle instance de la classe Carnivore
     * @param type espece de carnivores
     */
    Carnivore(string type, int pattes, bool doux);
    
    /** presentation des caracteristiques ddu carnivore */
    void presente();
};
