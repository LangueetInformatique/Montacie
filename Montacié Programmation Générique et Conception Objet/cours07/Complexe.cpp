#include "Complexe.h"

// constructeurs
Complexe::Complexe (float a, float b) {reel = a; imag = b;}
Complexe::Complexe () {reel = 0; imag = 0;}

// accesseurs
float Complexe::getreel () const {return reel;}
float Complexe::getimag () const {return imag;}

// red�finition de l'op�rateur + 
Complexe Complexe::operator + (const Complexe & y) const {
Complexe res(0,0);
res.reel = reel + y.reel; res.imag = imag + y.imag; return res; }

// red�finition de l'op�rateur *
Complexe Complexe::operator * (const Complexe & y) const {
Complexe res(0,0);
res.reel = reel*y.reel - imag*y.imag; 
res.imag = reel*y.imag + imag*y.reel;
return res; }

// red�finition de l�envoi sur le flot de sortie (fonction amie de la classe Complexe)
ostream & operator << (ostream & S, const Complexe & y) {
S << y.getreel() << " " << y.getimag() << endl;
return S; 
}

// red�finition de la r�ception sur le flot d�entr�e (fonction amie de la classe Complexe)
istream & operator >> (istream & S, Complexe & y) {
S >> y.reel >> y.imag; 
return S; 
} 




