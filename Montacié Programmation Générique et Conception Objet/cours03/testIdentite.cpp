/*
 * testIdentite.cpp
 *
 *  Created on: 1 févr. 2016
 *      Author: montacie
 */


#include "Identite.h"

int main (int argc, char *argv[]) {
Identite Id1("Ducrut","Lucie"), Id2 ("Herbrant","Claude"), Id;
cout << "Entrez une identite : ";
cin >> Id;
cout << (Id1==Id2) << "  " << (Id1==Id1) << endl;
cout << Id1+Id2 << Id;

return 0;
}


