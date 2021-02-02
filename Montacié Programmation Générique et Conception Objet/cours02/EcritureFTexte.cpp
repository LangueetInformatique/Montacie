/**
 * @file EcritureFTexte.cpp
 * @author montacie
 * @brief Ecriture d'un fichier texte (avec tableau de char)
 * @version 1 29/12/05
 * Programmation générique et conception objet
 */
#include <iostream>
#include <fstream>
using namespace std;


main() {

	char nomFichier[255];
	cout << "Nom du fichier à écrire : ";
	cin.getline(nomFichier, 255);  	// extraction du rc
		
	ofstream flotOut;				// fOut : le fichier de sortie
	flotOut.open(nomFichier, ios::out);		// ouverture du fichier flotOut
	
	if (flotOut.fail()) {
		cerr << "Erreur : impossible d'écrire dans le fichier "
		<< nomFichier << endl;
	} 
	else {
		int noL=0;
		char phrase[1000];
		cout << "Entrez votre texte (pour terminer,\n";
		cout << "'.' en début de ligne) :\n";
		do {
//			cout << "Entrez une phrase :" << endl;
			cin.getline(phrase, 1000); 		// extraction du rc
			flotOut << "L" << ++noL <<" : " << phrase << endl;
		} while (phrase[0]!='.');
		
		flotOut.close();
	}
}
