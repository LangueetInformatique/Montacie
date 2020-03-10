#include <iostream>
#include <list>
#include "Date.h"

using namespace std;
int main() {

	list<Date> ld;
	Date fin, d;
	cin >> d;
	do {
		ld.insert(ld.end(), d);
		cin >> d;
	} while (d != fin);

	cout << "liste de " << ld.size() << " elements" << endl;
	ld.sort();
	cout << "entre " << ld.front();
	ld.reverse();
	cout << "et " << ld.front() << endl;
}
