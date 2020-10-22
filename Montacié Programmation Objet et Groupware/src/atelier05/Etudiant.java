package atelier05;

public class Etudiant {
	String nom, prenom;
	int numeroEtudiant;

	/**
	 *  constructeur vide
	 */
	public Etudiant() {
		
	}
	
	/**
	 *  constructeur non vide
	 */
	public Etudiant(String nom, String prenom, int numero) {
		this.nom = nom;
		this.prenom = prenom;
		this.numeroEtudiant = numero;
		
	}

}
