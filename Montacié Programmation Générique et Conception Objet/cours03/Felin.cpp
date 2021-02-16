/*
 * Felin.cpp
 *
 *
 */

#include "Felin.h"

/** Creation d'une nouvelle instance de la classe Felin
 * @param type espece de felins
 */
Felin::Felin(string type) : Animal (type, 4) {
    domestique = false;
}
    
/** presentation des caracteristiques du felin */
void Felin::presente() {
	Animal::presente();
    string etat = (domestique) ? "domestique" : "sauvage";         
    cout << "je suis vraiment un animal " << etat << endl;   
}
    
/** cri du felin */
void Felin::crie() {
	cout << "je rugis, et  j'ai faim  ..." << endl;
}
