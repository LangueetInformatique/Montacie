/*
 * F�lin.h
 *
 * Created on 25 octobre 2002, 17:42
 */

#include "Animal.h"

/** Cr�ation et gestion de f�lins
 * @author montacie
 */
class Felin : public Animal {
protected:
    /** est-ce un animal domestique ? */    
    bool domestique;
public:
    /** Cr�ation d'une nouvelle instance de la classe F�lin
     * @param type esp�ce de f�lins
     */
    Felin(string type);
    
    /** pr�sentation des caract�ristiques du f�lin */
    void presente();
    
    /** cri du f�lin */
    void crie();
    
};
