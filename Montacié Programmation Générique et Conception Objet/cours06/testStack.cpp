#include <iostream>
#include <vector>
#include <stack>
#include "../cours03/Animal.h"
using namespace std;

int main() {
	stack<Animal, vector<Animal> > pa;

	pa.push(*(new Animal("lion", 4)));
	pa.push(*(new Animal("kangourou", 2)));
	pa.push(*(new Animal("araignee", 6)));

	while (pa.empty() == false) {
		pa.top().presente();
		pa.pop();
	}

}
