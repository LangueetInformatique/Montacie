#include <iostream>
#include <set>
#include <string>
#include <functional>

using namespace std;

typedef multiset <string> msString;
typedef msString::iterator iMsString;
int main() {
	msString amb;
	amb.insert("canapé"); amb.insert("tapis"); amb.insert("table");
	amb.insert("chaise"); amb.insert("chaise");amb.insert("bureau");
	amb.insert("lampe"); amb.insert("fauteuil"); 
	
	for (iMsString it = amb.begin();it != amb.end(); it++)
		cout << *it << " ";
	cout << endl << amb.count("chaise"); 

}
