#ifndef OMNIVORE_H_
#define OMNIVORE_H_

#endif /*OMNIVORE_H_*/

/*
 * Omnivore.h
 *
 * Created on 15 mars 2006, 19:41
 */

#include "Herbivore.h"
#include "Carnivore.h"

/** Cr�ation et gestion d'omnivores
 * @author montacie
 */
class Omnivore : public Herbivore, public Carnivore {
public:
    /** Cr�ation d'une nouvelle instance de la classe Omnivore
     * @param type esp�ce de omnivores
     */
    Omnivore(string type, int pattes);
    
    /** pr�sentation des caract�ristiques de l'omnivore */
    void presente();

   /** cri de l'animal */
    void crie();
};
