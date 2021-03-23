#ifndef PATIENT_H_
#define PATIENT_H_

#include <iostream>			// déclaration des flots standard
#include <string>
using namespace std;

class Patient {
private:
	int age;
	char sexe;
public:
	string nom;
	Patient();
	Patient(string n, int a, char s);
	// fonction de comparaison
	bool operator >= (const Patient & p) const;
};
#endif /*PATIENT_H_*/
