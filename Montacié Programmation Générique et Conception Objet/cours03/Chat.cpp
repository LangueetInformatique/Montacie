/*
 * Chat.cpp
 *
 * Created on 25 octobre 2002, 17:35
 */

#include "Chat.h"

/** création d'une nouvelle instance de la classe Chat
 * @param LeNom nom du chat
 */
Chat::Chat(string LeNom) : Felin ("Chats") {
    nom = LeNom;
    domestique = true;
}

/** création d'une nouvelle instance de la classe Chat
 */
Chat::Chat() : Felin ("Chats") { // constructeur vide 
    domestique = true;
}

/** accesseur en écriture de l'attribut du chat
 */
void Chat::setNom(string LeNom){ 
	if (nom.compare("") != 0) nom = LeNom;
}
    
/** présentation des caractéristiques du chat */    
void Chat::presente() {
	Felin::presente(); 
    cout << "je m'appelle " << nom << endl;
}
    
/** cri du chat */    
void Chat::crie() {
	cout << "je miaule  ..." << endl;
}
