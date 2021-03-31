#include "cttl/cttl.h"
#include <string>
using namespace cttl;

using std::cout;
using std::endl;
using std::string;

class Grammaire {
static size_t item( const_edge<policy_space<> >& e) {
    return (symbol("caractere") | symbol("mot") | symbol("ligne") | symbol("page") ).match(e);
}
static size_t dir( const_edge<policy_space<> >& e) {
    return (symbol("haut") | symbol("bas") | symbol("gauche") | symbol("droite") ).match(e);
}
static size_t ecmd( const_edge<policy_space<> >& e) {
    return ( symbol("fin") + *symbol("inserer") ).match(e);
}
static size_t icmd( const_edge<policy_space<> >& e) {
    return symbol("inserer").match(e);
}
static size_t dcmd( const_edge<policy_space<> >& e) {
    return ( symbol("detruire") + *rule(item) ).match(e);
}
static size_t mcmd( const_edge<policy_space<> >& e) {
    return ( symbol("bouger") + rule(dir) ).match(e);
}
public:
static size_t start( const_edge<policy_space<> >& e) {
    return ( rule(mcmd) | rule(dcmd) | rule(icmd) + rule(ecmd) ).match(e);
}
};

void appartient(string s) {
	const_edge<policy_space<> > e = *(new const_edge<policy_space<> >(s, 0, s.size()));
	if (rule(Grammaire::start).match(e) == 0) 
		cout << s << " appartient au langage" << endl;
	else
		cout << s << " n'appartient pas au langage" << endl;
}

int main() {	
	appartient ("bouger bas"); 
	appartient ("detruire caractere"); 
	appartient ("bouger caractère");
	
	return 0;
}
