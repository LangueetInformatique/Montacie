#include "TableauDyn.h"
#include "../cours01/Etudiant.h"
#include "../cours03/Identite.h"

int main() {
TableauDyn <Etudiant> t1(0,1);
Etudiant Pascal;
Pascal.putnote(3, 15);
t1.ecrire(0, Pascal);

Etudiant e = t1.lire(0);
cout << e.getnote(3) << endl;

TableauDyn <Identite> t2(1,2);
Identite i1("Montacié","Claude"), i2;
i2 = i1 + i1;
t2.ecrire(1, i2);

i1 = t2.lire(1);
cout << i1 << endl;


return 0;
}
