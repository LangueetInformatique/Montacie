/*
 * Felin.h
 *
 *
 */

#include "Animal.h"

/** Creation et gestion de felins
 * @author montacie
 */
class Felin : public Animal {
protected:
    /** est-ce un animal domestique ? */    
    bool domestique;
public:
    /** Creation d'une nouvelle instance de la classe Felin
     * @param type espece de felins
     */
    Felin(string type);
    
    /** presentation des caracteristiques du felin */
    void presente();
    
    /** cri du felin */
    void crie();
    
};
