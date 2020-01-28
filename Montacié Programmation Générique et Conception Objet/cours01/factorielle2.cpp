#include "factorielle2.h"

int main(int argc, char* argv[]) {
	int n;
	cin >> n;
	cout << "la factorielle de " << n << " est égale à " << fact(n) << endl;
	return (0);
}

int fact(const int& n) { // protection de la variable n
	int res = 1, i;
	for (i = 1; i <= n; i++)
		res = res * i;
	return (res);
}
