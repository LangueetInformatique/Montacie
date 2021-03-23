#include <iostream>
#include <map>
#include <string>

using namespace std;

typedef multimap<int, string, less<int> > mmIntString;
typedef mmIntString::iterator iMmIntString;

int main() {
	mmIntString conjug;   
	conjug.insert(make_pair(1, "parler"));
	conjug.insert(make_pair(2, "choisir"));
	conjug.insert(make_pair(3, "prendre"));
	conjug.insert(make_pair(2, "finir"));
	conjug.insert(make_pair(1, "manger"));
	
	pair <iMmIntString, iMmIntString> it2;
	it2 = conjug.equal_range(2); 

	for (iMmIntString it = it2.first;it != it2.second;it++)
		cout << it->second << " "; 
}
