/*
 * testConstruction.cpp
 *
 *  Created on: 4 mai 2010
 *      Author: montacie
 */

#include <iostream>
#include <string>
#include "suds/SSTree.h"
#include "suds/Tools.h"
using namespace std;

int main()
{
	cout << "lecture au clavier du mot" << endl;
	//string A; cin >> A;
	string A ="ABCFABCDABFABCDABCDABDE";
	SSTree *sst = new SSTree((uchar*)(A.c_str()), A.size()+1);
	// Affichage de l'arbre de suffixes
    sst->PrintTree(0, 0);

    return 0;
}



