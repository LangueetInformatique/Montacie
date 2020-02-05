/*
 * Identite.h
 *
 *  Created on: 1 févr. 2016
 *      Author: montacie
 */

#ifndef IDENTITE_H_
#define IDENTITE_H_

#endif /* IDENTITE_H_ */


#include <string>
#include <iostream>
using namespace std;

class Identite {
private :
string nom_, prenom_;
public :
Identite (string n, string p); // constructeurs
Identite ();
string nom() const; // accesseurs
string prenom() const;

bool operator == (const Identite & y) const; // redefinition de ==
Identite operator + (const Identite & y) const; // redefinition de +


// redefinition par une fonction externe amie de la reception sur le flot d'entree
friend istream & operator >> (istream & S, Identite & y);
// redefinition de l'envoi sur le flot de sortie
friend ostream & operator << (ostream & S, const Identite & y);
};
