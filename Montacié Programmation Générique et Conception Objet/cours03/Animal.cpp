/*
 * Animal.cpp
 *
 *
 */

#include "Animal.h"


/** cr�ation d'une nouvelle instance de la classe Animal
 * @param type nom de l'esp�ce
 * @param pattes nombre de pattes
 */
Animal::Animal(string type, int pattes) {
	espece=type; 
    nb_pattes = pattes;  
}
    
/** pr�sentation des caract�ristiques de l'animal
 */
void Animal::presente() {
    cout << "je suis un repr�sentant de l'esp�ce des " << espece << " et j'ai "
		<< nb_pattes << " pattes" << endl;
}
    
/** cri de l'animal
  */
void Animal::crie() {
    cout << "j'existe, donc je crie ..." << endl;
}
    
 /** redefinition de l'operateur == */
 bool Animal::operator == (const Animal & a) {
 	if (nb_pattes != a.nb_pattes) return false;
 	if (espece != a.espece) return false;
 	return true;
}

/** redefinition de l'operateur < */
 bool Animal::operator < (const Animal & a) const {
 	if (nb_pattes < a.nb_pattes) return true;
 	if (nb_pattes > a.nb_pattes) return false;
 	if (espece < a.espece) return true;
 	return false;
}

    
