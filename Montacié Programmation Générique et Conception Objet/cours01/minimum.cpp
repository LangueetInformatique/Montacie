#include "minimum.h"

// minimum de 2 entiers
int min(int x, int y) {
	if (x < y)
		return x;
	else
		return y;
}
// minimum de 3 entiers
int min(int x, int y, int z) {
	if (x < y) {
		if (x < z)
			return x;
		else
			return z;
	} else {
		if (y < z)
			return y;
		else
			return z;
	}
}

int main(int argc, char* argv[]) {
	int i, j, k;
	cout << "Entrez trois entiers " << endl;
	cin >> i >> j >> k;
	cout << min(i, j) << " " << min(i, j, k);
	return 0;
}
