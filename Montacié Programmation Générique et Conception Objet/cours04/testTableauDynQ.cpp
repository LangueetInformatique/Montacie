#include <string>

using namespace std;

#include "TableauDyn.h"
#include "../tp01/Date.h"
#include "../Cours01/Etudiant.h"

template <typename U, typename T> class TableauDynQ : public TableauDyn<T> {
	protected:
	U quality;
	public:
	TableauDynQ<U,T>(unsigned int c, int p, U q) : TableauDyn <T> (c, p) {
	quality = q;}
	U getQuality() {return quality;}
};

int main() {
	Etudiant Pascal;
	Pascal.putnote(3, 15);
	Date d(30,4,2006);
	
	TableauDynQ<Etudiant, Date> tq(0,1, Pascal);
	tq.ecrire(0, d);
	tq.getQuality();
	
	
}
