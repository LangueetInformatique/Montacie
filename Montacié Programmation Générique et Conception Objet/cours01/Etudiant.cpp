#include "Etudiant.h"
// constructeur vide (m_NombreNoteDef notes)
Etudiant::Etudiant() {
	m_NombreNote = m_NombreNoteDef;
	m_Tnote = new int[m_NombreNote];
}
// constructeur non vide 
Etudiant::Etudiant(int n) {
	m_NombreNote = n;
	m_Tnote = new int[m_NombreNote];
}
// destructeur
Etudiant::~Etudiant() {
	delete m_Tnote;
}

// ajouter une note
void Etudiant::putnote(int e, int n) {
	if (e < m_NombreNote)
		m_Tnote[e] = n;
}

// lire une note avec protection
int Etudiant::getnote(int e) const {
	if (e >= m_NombreNote)
		return -1;
	else
		return m_Tnote[e];
}
