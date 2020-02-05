/**
 * @file LectureNonRobuste.cpp
 * @author montacie
 * @brief exemple de lecture non robuste
 * @version 1 29/12/05
 * Programmation générique et conception objet
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	unsigned int nbLu;
	do {
		cout << "Entrez un nombre entre 1 et 10 : " << flush;
		cin >> nbLu;
	} while ((nbLu < 1) || (nbLu > 10));
	return 0;
}
