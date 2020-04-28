#include <iostream>
#include <functional>
#include <vector>
#include "../tp03/Complexe.h"
using namespace std;

int main()
{
	vector <Complexe> vc1, vc2;
	vc1.push_back(*new Complexe(0.4, 0.9));
	vc1.push_back(*new Complexe(-0.8, 0.5));
	vc1.push_back(*new Complexe(0.6, -0.1));
	vc1.push_back(*new Complexe(0.2, 0.1));
	
	// multiplication du vecteur de complexe par un complexe
	// sauvegarde dans vc2
	 transform(vc1.begin(), vc1.end(), vc2.begin(), multiplies<Complexe>());
	 
	
}