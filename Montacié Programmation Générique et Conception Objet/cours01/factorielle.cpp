#include "factorielle.h"

// point d'entrée de l'exécutable
int main(int argc, char* argv[]) {
	int n;
	cout << "Entrez un entier " << endl;
	cin >> n; // lecture de la variable n
	cout << "prod(" << n << ")=" << prod(n) << endl;
	cout << prod(n, 0) << endl;
	return (0);
}

int prod(int n, int i) {
	int res = 1;
	while (i <= n) {
		res = res * i;
		i++;
	}
	return (res);
}

