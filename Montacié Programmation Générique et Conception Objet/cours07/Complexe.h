#ifndef COMPLEXE_H_
#define COMPLEXE_H_

#endif /*COMPLEXE_H_*/

#include <iostream>
using namespace std;

class Complexe {
private :  
float reel, imag;
public :
Complexe (float a, float b); // constructeurs
Complexe ();
float getreel() const; // accesseurs
float getimag() const;

Complexe operator + (const Complexe & y) const; // red�finition de +
Complexe operator * (const Complexe & y) const; // red�finition de * 

// red�finition par une fonction externe amie de la r�ception sur le flot d�entr�e 
friend istream & operator >> (istream & S, Complexe & y);
// red�finition de l�envoi sur le flot de sortie
friend ostream & operator << (ostream & S, const Complexe & y);
};

