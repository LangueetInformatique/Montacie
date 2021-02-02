/**
 * @file ModificationFBinaire.cpp
 * @author l'equipe pedagogique
 * @brief Modification d'un fichier binaire
 * @version 1 - 23/12/15
 * Structures de donnees et algorithmes
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
	cout << "Modification d'un fichier binaire\n(deja cree) de caracteres" <<endl;
	
	fstream flotInOut;
	flotInOut.open("FileChar.bin", ios::in|ios::out|ios::binary);
	if (flotInOut.fail()) { 
		cerr << "Impossible de lire le fichier\n";
		exit(1); 
	}
	char d;
		
	/* calcul du nombre d'elements de type char dans le fichier */
    flotInOut.seekg(0, fstream::end);
    int nbChar = flotInOut.tellg() / sizeof(char);
    	
    if (nbChar>0) {
    	/* modification et enregistrement de l'element median du fichier */
    	flotInOut.seekg ((nbChar/2)*sizeof(char), ios::beg);
  		flotInOut.read((char*) &d, sizeof(char));
   		d++;
    	flotInOut.seekg ((nbChar/2)*sizeof(char), ios::beg);
   		flotInOut.write((char*) &d, sizeof(char));
   		flotInOut.flush();
    }
    /** lecture et affichage des dates du fichiers */
    flotInOut.seekg(0, ios::beg);
   	for (int i = 0; i < nbChar; ++i) {
   		flotInOut.read((char*)&d, sizeof(char));
   		cout << d;
    }
 
	flotInOut.close();
	return 0;
}


