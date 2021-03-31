#include "cttl/cttl.h"
#include "utils/fileio.h"

using namespace std;
using cttl::node;

int main()
{
	string texte;
	cttl::file2string("Data/livres/adelaide.txt", texte);
	node<> p1( texte ); p1.go_bof();
	node<> p2( texte ); p2.go_eof();

	cout << "ce texte comporte " << p2.offset() << " caracteres et " ;
	cout << p2.line()-1 << " lignes" << endl;
	// lecture du caractere j de la ligne i
	cout << "lecture du caractere j de la ligne i" << endl;
	int i,j; cin >> i >> j;
	p1.go_line_home(i+1);
	cout << p1.offset() << " " <<  p1[j] << endl; ;
	// insertion et decalage
	p1.insert_stay("insertion");
	cout << p1.offset() << " " << p2.offset() << endl ;
	p1.insert_go("destruction");
	cout << p1.offset() << " " << p2.offset() << endl ;
	
	return 0;
}
