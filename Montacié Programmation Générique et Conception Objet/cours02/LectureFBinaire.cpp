/**
 * @file LectureFBinaire.cpp
 * @author montacie
 * @brief Lecture d'un fichier binaire
 * @version 1 - 23/12/15
 * Programmation generique et conception objet
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	cout << "Lecture du fichier binaire" <<endl;
	
	ifstream flotIn;
	flotIn.open("FileChar.bin", ifstream::in|ifstream::binary);

	if (flotIn.fail()) cerr << "Impossible de lire le fichier\n";
	else {
		char d;
		
		/* calcul du nombre d'elements de type char dans le fichier */
    	flotIn.seekg(0, ifstream::end);
    	int nbChar = flotIn.tellg() / sizeof(char);
    	flotIn.seekg(0);
    	cout << "Le fichier contient " << nbChar << " caractères" << endl;
    
    	/** lecture et affichage des caractères du fichiers */
   		for (int i = 0; i < nbChar; ++i) {
   			flotIn.read((char*)&d, sizeof(char));
    		cout << d;
    	}
		cout << "\nFin de lecture" << endl;
		flotIn.close();
		return 0;
	}
}


