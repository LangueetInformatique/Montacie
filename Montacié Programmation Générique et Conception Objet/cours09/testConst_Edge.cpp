#include <string>
#include <vector>
#include "cttl/cttl.h"
#include "utils/fileio.h"

using namespace std;
using cttl::node;
using cttl::const_edge;

int main()
{
	string texte;
	cttl::file2string("Data/livres/adelaide.txt", texte);
	int i1 = -1, i2, n = 0;
	vector<const_edge<> > vs; 
	while ((i2 = texte.find('\n', i1+1)) != string::npos) {
		node<> p1(texte, i1+1); p1.offset(i1+1);
		node<> p2(texte, i2); p2.offset(i2);
		vs.push_back(*(new const_edge<>(p1, p2)));
		n++;
		i1 = i2;
	}
	cout << n << endl;
	// lecture de la ligne i
	int i; cin >> i; 
	cout << vs[i].first.offset() << " " << vs[i].second.offset() << endl;
	cout << vs[i].text() << endl;
	
	return 0;
}
