/**
 * @file LectureRobuste.cpp
 * @author montacie
 * @brief Exemple de lecture robuste
 * @version 1 29/12/05
 * Programmation générique et conception objet
 */
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

/**
 * @brief Saisie robuste d'un nombre naturel
 * @param[in] le message d'aide à la saisie
 * @return le nombre naturel saisi
 */
 unsigned int saisirNombreNaturel(const char* msgSaisie) {
	unsigned int n;
	cout << msgSaisie << flush;
	cin >> n;
	if (cin.fail()) { 	// teste l'état de cin 
		cout << "l'entrée n'est pas valide..." << endl;
		cin.clear(); 		// remets cin dans un état lisible
		cin.ignore(INT_MAX, '\n'); // ignore toute la ligne de données
	}
	return n;
}

int main() {
	unsigned int nb;
	char msg[]="Saisir un nombre entre 1 et 10 : ";
	do {
		nb=saisirNombreNaturel(msg);
	} while ((nb < 1) || (nb > 10));
	cout <<"Nombre lu : " << nb << endl;
	return 0;
}
