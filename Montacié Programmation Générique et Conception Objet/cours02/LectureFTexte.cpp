/**
 * @file LectureFTexteChar.cpp
 * @author montacie
 * @brief Lecture d'un fichier texte (avec tableau de char)
 * @version 1 29/12/05
 * SProgrammation générique et conception objet
 */
#include <iostream>
#include <fstream>
using namespace std;

main() {
	
	char nomFichier[255];
	cout << "Nom du fichier texte à lire\n";
	cout << "(donnez le chemin du projet au fichier) :\n" ;
	cin.getline(nomFichier, 255);  // extraction du rc
	
	ifstream fEntree;
	fEntree.open(nomFichier);
	
	if (fEntree.fail()) {
		cerr << "Impossible de lire le fichier " << nomFichier << endl;
	}
	else {
		string phrase;;
		while (!fEntree.eof()) {
			getline(fEntree, phrase); 
			cout << phrase << endl;
		}
		fEntree.close();
	}
}

