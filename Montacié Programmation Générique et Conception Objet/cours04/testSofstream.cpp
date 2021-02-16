#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "../cours03/Animal.h"

template <typename T> class Sofstream : public ofstream {
	public:
	void serialiser(T d) {write((char*) &d, sizeof(T));}
};

int main() {
	Sofstream <Animal> fc;
	fc.open("FileAnimal.bin", ofstream::out|ofstream::binary);
	Animal a("Blaireau", 4); 
	fc.serialiser(a);
	fc.close();	
}

