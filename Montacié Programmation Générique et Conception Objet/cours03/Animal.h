#ifndef ANIMAL_H_
#define ANIMAL_H_

#endif /*ANIMAL_H_*/

/*
 * Animal.h
 *
 *
 */

#include <iostream>
#include <string>
using namespace std;

/** Cr�ation et gestion d'animaux
 * @author montacie
 */
class Animal {
private:
	string espece;
    int nb_pattes;
public:
    /** cr�ation d'une nouvelle instance de la classe Animal
     * @param type nom de l'esp�ce
     * @param pattes nombre de pattes
     */
    Animal(string type, int pattes);
    
    /** pr�sentation des caract�ristiques de l'animal
     */
    void presente();

    /** cri de l'animal
     */
    void crie();
    
    bool operator == (const Animal & a);
    bool operator < (const Animal & a) const;
};
