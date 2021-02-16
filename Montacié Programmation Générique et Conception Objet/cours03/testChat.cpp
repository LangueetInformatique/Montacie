#include "Chat.h"
    
/**
 * @param args the command line arguments
 */
int main() {
	Animal a("oiseaux", 2);
    a.presente();
    a.crie();
	Chat ch("Félix");
    ch.presente();
    ch.crie();

	return 0;
}
