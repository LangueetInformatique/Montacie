/*
 * Chat.cpp
 *
 *
 */

#include "Chat.h"

/** creation d'une nouvelle instance de la classe Chat
 * @param LeNom nom du chat
 */
Chat::Chat(string LeNom) : Felin ("Chats") {
    nom = LeNom;
    domestique = true;
}

/** creation d'une nouvelle instance de la classe Chat
 */
Chat::Chat() : Felin ("Chats") { // constructeur vide 
    domestique = true;
}

/** accesseur en ecriture de l'attribut du chat
 */
void Chat::setNom(string LeNom){ 
	if (nom.compare("") != 0) nom = LeNom;
}
    
/** presentation des caracteristiques du chat */
void Chat::presente() {
	Felin::presente(); 
    cout << "je m'appelle " << nom << endl;
}
    
/** cri du chat */    
void Chat::crie() {
	cout << "je miaule  ..." << endl;
}
