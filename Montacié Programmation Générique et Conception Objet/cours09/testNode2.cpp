#include "cttl/cttl.h"
#include "utils/fileio.h"
# include <vector>

using namespace std;
using cttl::node;

int main()
{
	ifstream fEntree("Data/livres/adelaide.txt");
	string phrase, texte;
	vector<node<> > vp; 
	int n = 0;
	while (!fEntree.eof()) {
		getline(fEntree, phrase); phrase += "\n";
		vp.push_back(*(new node<>(texte)));
		vp[n].go_eof(); vp[n].insert_stay(phrase); 
		n++;
	}
	
	for (int i = 0;i < n;i++)
		cout << i << " " << vp[i].offset() << endl; 
}
