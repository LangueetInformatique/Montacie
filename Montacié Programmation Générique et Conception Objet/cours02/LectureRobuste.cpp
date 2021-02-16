/**
 * @file LectureRobuste.cpp
 * @author montacie
 * @brief Exemple de lecture robuste
 *
 * Programmation generique et conception objet
 */
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

/**
 * @brief Saisie robuste d'un nombre naturel
 * @param[in] le message d'aide a la saisie
 * @return le nombre naturel saisi
 */
 unsigned int saisirNombreNaturel(const char* msgSaisie) {
	unsigned int n;
	cout << msgSaisie << flush;
	cin >> n;
	if (cin.fail()) { 	// teste l'etat de cin
		cout << "l'entree n'est pas valide..." << endl;
		cin.clear(); 		// remets cin dans un etat lisible
		cin.ignore(INT_MAX, '\n'); // ignore toute la ligne de donnees
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
