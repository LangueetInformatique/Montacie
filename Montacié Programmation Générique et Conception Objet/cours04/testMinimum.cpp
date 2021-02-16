#include "Minimum.h"

#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {

float x, y; 
cout << "entrez deux reels : "; cin >> x >> y;
cout << Minimum(x, y) << endl;

int i, j; 
cout << "entrez deux entiers : "; cin >> i >> j;
cout << Minimum<int>(i, j) << endl;

float z; 
cout << "entrez trois reels : "; cin >> x >> y >> z;
cout << Minimum<float>(x, y, z) << endl;

int k; 
cout << "entrez trois entiers : "; cin >> i >> j >> k;
cout << Minimum<>(i, j, k) << endl;

return 0; 
}
