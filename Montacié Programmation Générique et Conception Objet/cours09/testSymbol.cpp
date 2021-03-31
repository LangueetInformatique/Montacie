#include "cttl/cttl.h"
#include "utils/fileio.h"
#include <string> 

using namespace cttl;
using std::cout;
using std::string;
using std::endl;

int main()
{
	string texte;
	file2string("Data/livres/adelaide.txt",texte);
	
	// recherche d'une chaine de caracteres
	edge<> e = *(new edge<>(texte, 0, texte.size()));

	int p = symbol("Hautcastel").find(e); 
		cout << p << " " << texte.substr(p, e.first.offset()-p) << endl;
	// recherche en boucle du motif a{n}
	while ((p = (symbol('a') + +symbol('n')).bang_find(e)) != std::string::npos) 
		cout << p << " " << texte.substr(p, e.first.offset()-p) << " ";

	
	return 0;
}

