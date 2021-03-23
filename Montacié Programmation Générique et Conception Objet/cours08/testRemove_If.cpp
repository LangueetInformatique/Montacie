#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <iterator>

using namespace std;
 
template<class T>class NomPropre {
public:
bool operator() (const T& s) {
  	if ((s.at(0) >= 'A') && (s.at(0) <= 'Z')) return true; else return false; 
  	}
};


int main() {
	list <string> ls;
	// lecture des mots de la phrase
	ifstream fEntree("Cours 08/Phrase.txt");
	istream_iterator<string> in_it(fEntree);
	copy(in_it, istream_iterator<string>(), back_inserter(ls));
	fEntree.close();
	
	list<string>::iterator it, itf;
	for (it = ls.begin(); it != ls.end();it++) cout << *it << " ";
	cout << endl;
	
	itf = remove_if(ls.begin(), ls.end(), NomPropre<string>()); 
	for (it = ls.begin(); it != itf;it++) cout << *it << " ";
	
	
}