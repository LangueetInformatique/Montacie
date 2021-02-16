#include "TableauDyn.h"
#include "../cours03/Chat.h"

class TableauDyn2Chat : public TableauDyn<Chat> {
	public:
	TableauDyn2Chat(unsigned int c, int p) : TableauDyn <Chat> (c, p) {}
	void presente() {for (int i= 0;i < capacite;i++) tab[i].presente();}
};

int main() {
	TableauDyn2Chat t(0,1);
	Chat c1("Felix"); t.ecrire(0, c1); 
	Chat c2("Potam"); t.ecrire(1, c2);
	t.presente(); 
}
