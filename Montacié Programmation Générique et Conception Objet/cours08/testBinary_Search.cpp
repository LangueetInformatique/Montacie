#include "../Cours 03/Animal.h"
#include <iostream>
#include <set>
#include <functional>

using namespace std;

int main() {
	set<Animal , less<Animal> > sa;
	// l'operateur < a du etre redefini pour Animal
	sa.insert(*new Animal("oiseau", 2));
	sa.insert(*new Animal("araignee", 8));
	sa.insert(*new Animal("insecte", 6));
	sa.insert(*new Animal("poisson", 0));
	sa.insert(*new Animal("mammifere", 4));
	
	Animal a(Animal("mammifere", 4));
	if (binary_search(sa.begin(), sa.end(), a) == false)
		cout << "Je ne connais pas cet animal" << endl;
	else
		cout << "Je connais cet animal" << endl;
	
}