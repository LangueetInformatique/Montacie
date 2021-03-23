#include "Patient.h"


Patient::Patient() {	// Constructeur vide
}


Patient::Patient(string n, int a, char s) { // Constructeur avec initialisation
	nom = n;
	age = a;
	sexe = s;
}

bool Patient::operator >= (const Patient & p) const {
	if (age < p.age) return true; 
	if (age > p.age) return false; 
	if (sexe == p.sexe) return true;
	if (sexe == 'H') return true;
	return false;
}

