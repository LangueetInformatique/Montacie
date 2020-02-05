/*
 * Chat.h
 *
 * Created on 25 octobre 2002, 17:35
 */

#include "Felin.h"

/** Création et gestion de chats
 * @author montacie
 */
class Chat : public Felin {
private:
    string nom;
public:
    /** création d'une nouvelle instance de la classe Chat
     * @param LeNom nom du chat
     */
    Chat(string LeNom);

   /** création d'une nouvelle instance de la classe Chat */
    Chat();
	
	/** accesseur en écriture de l'attribut du chat */
	void setNom(string LeNom); 
    
    /** présentation des caractéristiques du chat */    
    void presente();
    
    /** cri du chat */    
    void crie();
};
