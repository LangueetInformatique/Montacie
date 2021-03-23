#include "Patient.h"

#include <iostream>
#include <set>
#include <functional>

using namespace std;

typedef set <Patient, greater_equal <Patient> > sPatient;
typedef sPatient::iterator itsPatient;

int main() {
	sPatient sp;
	sp.insert(*new Patient("Line", 25, 'F'));
	sp.insert(*new Patient("Lucie", 10, 'F'));
	sp.insert(*new Patient("Simon", 9, 'H'));
	sp.insert(*new Patient("Eric", 25, 'H'));
	sp.insert(*new Patient("Jean", 26, 'H'));
	
	for (itsPatient it = sp.begin();it != sp.end(); it++)
		cout << it->nom << " ";
}