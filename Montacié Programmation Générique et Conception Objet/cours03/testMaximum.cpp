#include <iostream>
using namespace std;

int Maximum(int i, int j){
return i > j ? i : j;
}

float Maximum(float x, float y){
return x > y ? x : y;
}

int main (int argc, char *argv[]) {
float x, y; 
cout << "entrez deux réels : "; cin >> x >> y;
cout << Maximum(x, y) << endl;

int i, j; 
cout << "entrez deux entiers : "; cin >> i >> j;
cout << Maximum(i, j) << endl;
}


