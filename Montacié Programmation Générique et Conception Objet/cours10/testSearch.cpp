/*
 * testSearch.cpp
 *
 *  Created on: 5 mai 2010
 *      Author: claude
 */

#include <iostream>
#include <string>
#include "suds/SSTree.h"
#include "suds/Tools.h"
using namespace std;

int main() {
	string A; char c;
	ifstream fs("Data/livres/adolphe.txt");
	while (!fs.eof()) { fs.get(c); A += c;}
	fs.close();
	SSTree *sst = new SSTree((uchar*)(A.c_str()), A.size()+1);
	cout << "lecture au clavier du mot" << endl;
	string B; cin >> B;
	ulong i =  sst->search((uchar*)(B.c_str()), B.size());
	cout << "le numero du noeud est " << i << endl;
	cout << "il correspond au texte " << sst->pathlabel(i) << endl;
	ulong d = sst->textpos(i);
	cout << "dont la position est " << d << endl;

    return 0;
}

