/*
 * Identite.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: montacie
 */

#ifndef IDENTITE_CPP_
#define IDENTITE_CPP_

#endif /* IDENTITE_CPP_ */

#include "Identite.h"

// constructeurs
Identite::Identite (string n, string p) {nom_ = n; prenom_ = p;}
Identite::Identite () {nom_ = ""; prenom_ = "";}

// accesseurs
string Identite::nom () const {return nom_;}
string Identite::prenom () const {return prenom_;}

// redefinition de l'operateur +
bool Identite::operator == (const Identite & y) const {
	if (nom().compare(y.nom()) != 0) return false;
	if (prenom().compare(y.prenom()) != 0) return false;
	return true;
}

// redefinition de l'operateur +
Identite Identite::operator + (const Identite & y) const {
Identite res(nom() + "-" + y.nom(), prenom());
return res;
}

// redefinition de l'envoi sur le flot de sortie (fonction amie de la classe Identite)
ostream & operator << (ostream & S, const Identite & y) {
S << y.nom() << " " << y.prenom() << endl;
return S;
}

// redefinition de la reception sur le flot d'entree (fonction amie de la classe Identite)
istream & operator >> (istream & S, Identite & y) {
S >> y.nom_ >> y.prenom_;
return S;
}



