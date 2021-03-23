#include "../Cours 03/Animal.h"
#include <iostream>
#include <list>
#include <functional>

using namespace std;

int main() {
	list<Animal> la;
	la.push_front(*new Animal("oiseau", 2));
	la.push_front(*new Animal("araignee", 8));
	la.push_front(*new Animal("insecte", 6));
	la.push_front(*new Animal("poisson", 0));
	la.push_front(*new Animal("mammifere", 4));
	
	Animal a(Animal("mammifere", 2));
	// l'operateur == a du etre redefini pour Animal
	if (find(la.begin(), la.end(), a) == la.end())
		cout << "Je ne connais pas cet animal" << endl;
	else
		cout << "Je connais cet animal" << endl;
	
}