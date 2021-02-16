/*
 * Chat.h
 *
 *
 */

#include "Felin.h"

/** Creation et gestion de chats
 * @author montacie
 */
class Chat : public Felin {
private:
    string nom;
public:
    /** creation d'une nouvelle instance de la classe Chat
     * @param LeNom nom du chat
     */
    Chat(string LeNom);

   /** creation d'une nouvelle instance de la classe Chat */
    Chat();
	
	/** accesseur en ecriture de l'attribut du chat */
	void setNom(string LeNom); 
    
    /** presentation des caracteristiques du chat */
    void presente();
    
    /** cri du chat */    
    void crie();
};
