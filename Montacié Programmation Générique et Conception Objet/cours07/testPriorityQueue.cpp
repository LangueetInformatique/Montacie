#include "Patient.h"

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main() {
	priority_queue<Patient, vector<Patient>, greater_equal <Patient> > fpp;
	
	fpp.push(*new Patient("Line", 25, 'F'));
	fpp.push(*new Patient("Lucie", 10, 'F'));
	fpp.push(*new Patient("Simon", 9, 'H'));
	fpp.push(*new Patient("Eric", 25, 'H'));
	fpp.push(*new Patient("Jean", 26, 'H'));
	
	
	cout << fpp.size() << endl;
	Patient p;	
	while (fpp.empty() == false) {
		p = fpp.top(); fpp.pop();
		cout << p.nom << " ";
	}

	
	
}


