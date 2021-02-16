/**
 * @file TableauDyn.h
 * @author montacie 
 * @version 1 19/02/06
 * @brief Composant de tableau dynamique d'items
 * Programmation générique et conception objet
 */
 
#include <iostream> // déclaration des flots standard
#include <cassert>
using namespace std;

// classe générique de tableau dynamique
template <typename T> class TableauDyn {
protected :
	unsigned int capacite; 	   	// capacité du tableau tab
	unsigned int pasExtension; 	// pas d'extension du tableau
	T* tab;				   		// tableau alloué en mémoire dynamique
	void agrandir();
public :
	TableauDyn(unsigned int c, int p);
	~TableauDyn();
	T lire(unsigned int i) const;
	void ecrire(unsigned int i, T it);
	int getCapacite();
};

/**
 * @brief constructeur du tableau d'items dynamique 
 * caractérisé par un pas d'extension (p)
 * Allocation en mémoire dynamique du tableau d'items 
 * de capacité (c) caractérisé par un pas d'extension (p)
 * @param [in] c : capacité du tableau
 * @param [in] p : capacité du tableau
 */
template <typename T> TableauDyn<T>::TableauDyn(unsigned int c, int p) {
	assert((c>=0) && (p>0));
	capacite = c;
	pasExtension = p;
	// arrêt du programme en cas d'erreur d'allocation
	tab = new T[capacite];
}


/**
 * @brief destructeur du tableau d'items en mémoire dynamique
 */
template <typename T>TableauDyn<T>::~TableauDyn() {
	delete [] tab;
	tab = NULL;
}

/**
 * @brief Lecture d'un item d'un tableau d'items
 * @param[in] i : l'indice de l'item dans le tableau
 * @return l'item au poste i
 * @pre i < nbItems   
 */
template <typename T> T TableauDyn<T>::lire(unsigned int i) const {
	assert(i < capacite);
	return tab[i];
}

/**
 * @brief Ecrire un item dans un tableau d'items
 * @param[in] i : l'indice où écrire l'item
 * @param[in] item : l'item à écrire
 * @pre i <= capacite   
 */
template <typename T> void TableauDyn<T>::ecrire(unsigned int i, T it) {
	assert(i>=0);
	while (i >= capacite) agrandir();
	tab[i] = it;
}

/**
 * @brief Lecture de la capacite du tableau d'items
 * @return capacite du tableau
 */
 template <typename T> int TableauDyn<T>::getCapacite() {
 	return capacite;
}
 

/**
 * @brief Agrandir un tableau d'items de son pas d'extension
 */
template <typename T> void TableauDyn<T>::agrandir() {
	/* Allocation d'un tableau de (capacite + pasExtension) items */
	T* newT = new T[capacite + pasExtension];
	/* Recopie des (capacite) éléments du tableau dans le nouveau tableau */
	for (unsigned int i = 0; i < capacite; ++i)
		newT[i] = tab[i];
	/* Désallocation de l'ancien tableau d'items */
	delete [] tab;
	/* Mise à jour de tab et de la capacité du nouveau tableau 
	 * résultant de l'extension de capacité */
	tab = newT;
	capacite += pasExtension;
}
