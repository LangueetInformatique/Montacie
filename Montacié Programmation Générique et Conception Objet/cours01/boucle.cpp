/*
 * boucle.cpp
 *
 *
 *      Author: montacie
 */

// déclaration des flots standard
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {

	vector<string> v = {"hello", "cruel", "world"};
	for (string s: v)
		cout << s << endl;

}


