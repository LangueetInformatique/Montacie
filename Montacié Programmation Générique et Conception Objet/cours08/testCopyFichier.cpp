#include <iostream>
#include <fstream>
#include <list>
#include <iterator>

#include "../tp03/Date.h"

using namespace std;
int main() {
	
	list <Date> ld;
	ld.push_front(*new Date(19, 11, 1703));
	ld.push_front(*new Date(15, 1, 1992)); 
	ld.push_front(*new Date(5, 5, 1821));
	ld.push_front(*new Date(9, 3, 1796));
	ld.push_front(*new Date(11, 2, 660));
	ld.push_front(*new Date(29, 8, 1842));
	ld.push_front(*new Date(24, 4, 1617));
	
	// écriture d'une liste dans un fichier
	ofstream flotOut("Cours 08/Date.txt");				
	ostream_iterator<Date> out_it(flotOut);
	copy(ld.begin(), ld.end(), out_it);
	flotOut.close();
}