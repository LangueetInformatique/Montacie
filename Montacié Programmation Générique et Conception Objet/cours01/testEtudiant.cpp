#include "testEtudiant.h"
#include "Etudiant.h"

int main() {
// construction de deux objets de la classe etudiant
	Etudiant Pascal, Pierre(15);

// appel par l'objet Pascal à la méthode putnote
	Pascal.putnote(3, 15);

// appel par l'objet Pascal à la méthode getnote
	cout << Pascal.getnote(3);
	return 0;
}
