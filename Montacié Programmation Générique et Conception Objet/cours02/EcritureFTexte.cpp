/**
 * @file EcritureFTexte.cpp
 * @author montacie
 * @brief Ecriture d'un fichier texte (avec tableau de char)
 *
 * Programmation generique et conception objet
 */
#include <iostream>
#include <fstream>
using namespace std;


int main() {

	char nomFichier[255];
	cout << "Nom du fichier a ecrire : ";
	cin.getline(nomFichier, 255);  	// extraction du rc
		
	ofstream flotOut;				// fOut : le fichier de sortie
	flotOut.open(nomFichier, ios::out);		// ouverture du fichier flotOut
	
	if (flotOut.fail()) {
		cerr << "Erreur : impossible d'ecrire dans le fichier "
		<< nomFichier << endl;
	} 
	else {
		int noL=0;
		char phrase[1000];
		cout << "Entrez votre texte (pour terminer,\n";
		cout << "'.' en debut de ligne) :\n";
		do {
//			cout << "Entrez une phrase :" << endl;
			cin.getline(phrase, 1000); 		// extraction du rc
			flotOut << "L" << ++noL <<" : " << phrase << endl;
		} while (phrase[0]!='.');
		
		flotOut.close();
	}
}
