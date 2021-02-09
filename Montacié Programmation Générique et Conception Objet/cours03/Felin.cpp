/*
 * Félin.cpp
 *
 * Created on 25 octobre 2002, 17:42
 */

#include "Felin.h"

/** Création d'une nouvelle instance de la classe Félin
 * @param type espèce de félins
 */
Felin::Felin(string type) : Animal (type, 4) {
    domestique = false;
}
    
/** présentation des caractéristiques du félin */
void Felin::presente() {
	Animal::presente();
    string etat = (domestique) ? "domestique" : "sauvage";         
    cout << "je suis vraiment un animal " << etat << endl;   
}
    
/** cri du félin */
void Felin::crie() {
	cout << "je rugis, et  j'ai faim  ..." << endl;
}
