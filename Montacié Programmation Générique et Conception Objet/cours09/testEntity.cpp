#include "cttl/cttl.h"
#include "utils/fileio.h"
#include <string> 

using namespace cttl;
using std::cout;
using std::string;
using std::endl;

size_t NomPropre(const_edge<>& edge_ ) {
    string maj = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string min = "abcdefghijklmnopqrstuvwxyz���";
        return 
 		(
        	entity(maj)
            +
            +entity(min)
         ).bang_find(edge_);
    }

int main()
{
	string texte;
	file2string("Data/livres/adelaide.txt", texte);
	
	// recherche en boucle du motif maj{min}
	const_edge<> e = *(new const_edge<>(texte, 0, texte.size()));
	int p;
	while ((p = NomPropre(e)) != std::string::npos) 
		cout << p << " " << texte.substr(p, e.first.offset()-p) << " ";

	return 0;
}
