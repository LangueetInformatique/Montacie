/**
 * @file EcritureFBinaire.cpp
 * @author montacie
 * @brief Ecriture d'un fichier binaire
 * @version 1 29/12/14
 * Programmation generique et conception objet
 */
#include <iostream>
#include <fstream>

using namespace std;

int main() {

	ofstream flotOut;
	flotOut.open("FileChar.bin", ofstream::out|ofstream::binary);

	if (flotOut.fail()) cerr << "Impossible d'ecrire dans le fichier\n";
	else {
		char d;
		int nCar;
		cout << "Saisie de caractères a enregistrer dans le fichier" << endl;
		cout << "nombre de caracteres ?" << endl;
		cin >> nCar;
		for (int i = 0;i < nCar;i++) {
			cout << "?" << endl;
			cin >> d;
			cout << d << endl;
			flotOut.write((char*) &d, sizeof(d));
		}
		
		flotOut.close();
		return 0;
	}
}
