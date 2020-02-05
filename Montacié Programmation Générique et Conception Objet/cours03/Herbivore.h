#ifndef HERBIVORE_H_
#define HERBIVORE_H_

#endif /*HERBIVORE_H_*/

/*
 * Herbivore.h
 *
 * Created on 15 mars 2006, 19:29
 */

#ifndef ANIMAL_H_
#include "Animal.h"
#endif

/** Cr�ation et gestion d'herbivore
 * @author montacie
 */
class Herbivore : public Animal {
protected:
    /** est-ce un ruminant ? */    
    bool ruminant;	
public:
    /** Cr�ation d'une nouvelle instance de la classe Herbivore
     * @param type esp�ce d'herbivores
     */
    Herbivore(string type, int pattes, bool ruminant);
    
    /** pr�sentation des caract�ristiques de l'herbivore */
    void presente();
};
