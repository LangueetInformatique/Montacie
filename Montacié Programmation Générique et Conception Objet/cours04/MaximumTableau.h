#ifndef MAXIMUMTABLEAU_H_
#define MAXIMUMTABLEAU_H_

#endif /*MAXIMUMTABLEAU_H_*/

// Fonction template prenant en paramètre un tableau d'Item et sa taille
// et un foncteur :
template <typename T, typename F>
int MaximumTableau(T t, int taille, F foncteurCmp) {
	int max = 0;
	for (int i = 1;i < taille;i++) {
		if (foncteurCmp(t.lire(max), t.lire(i)) < 0)
			max = i;
	}
    return max;
}
