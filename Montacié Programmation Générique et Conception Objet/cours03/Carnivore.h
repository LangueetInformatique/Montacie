#ifndef CARNIVORE_H_
#define CARNIVORE_H_

#endif /*CARNIVORE_H_*/

/*
 * Carnivore.h
 *
 * Created on 15 mars 2006, 19:38
 */

#ifndef ANIMAL_H_
#include "Animal.h"
#endif

/** Cr�ation et gestion de carnivores
 * @author montacie
 */
class Carnivore : public Animal {
protected:
    /** est-ce un animal doux ? */    
    bool doux;
public:
    /** Cr�ation d'une nouvelle instance de la classe Carnivore
     * @param type esp�ce de carnivores
     */
    Carnivore(string type, int pattes, bool doux);
    
    /** pr�sentation des caract�ristiques ddu carnivore */
    void presente();
};
