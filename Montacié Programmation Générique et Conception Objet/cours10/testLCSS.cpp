/*
 * testLCSS.cpp
 *
 *  Created on: 5 mai 2010
 *      Author: montacie
 */

#include <iostream>
#include <fstream>
#include <string>
#include "suds/SSTree.h"
#include "suds/Tools.h"


using namespace std;

string lcss(string A, string B);

int main()
{
	string A, B; char c;
	ifstream fs1("Data/livres/candide.txt");
	while (!fs1.eof()) { fs1.get(c); A += c;}
	fs1.close();
	ifstream fs2("Data/livres/l'histoire de l'archiduc albert.txt");
	while (!fs2.eof()) { fs2.get(c); B += c;}
	fs2.close();

	cout << "le plus long facteur commun entre les deux livres est " << endl << lcss(A,B) << "\n\n";


    return 0;
}



