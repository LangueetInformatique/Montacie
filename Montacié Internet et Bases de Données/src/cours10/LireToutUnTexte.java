package cours10;

public interface LireToutUnTexte extends java.rmi.Remote {

	/** lecture d'un fichier texte dans la cha�ne sTexte 
	 * @param ft nom du fichier 
	 */
	public void Initialisation(String ft) throws java.rmi.RemoteException;
	/** Recherche du nombre d'occurrences de s dans sTexte
	 * @param s cha�ne cherch�e
	 * @return nombre d'occurrences 
	 */
	public int Chercher(String s) throws java.rmi.RemoteException;
	
	/** Affichage du contexte des occurrences de s dans sTexte
	 * @param s cha�ne cherch�e
	 * @param taille taille du contexte
	 */
	public void ChercherVoir(String s, int taille) throws java.rmi.RemoteException;

}
