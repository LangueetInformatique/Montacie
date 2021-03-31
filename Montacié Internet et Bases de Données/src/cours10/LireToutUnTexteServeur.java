package cours10;

import java.io.*;
import java.rmi.server.UnicastRemoteObject;
import java.text.BreakIterator;

public class LireToutUnTexteServeur extends UnicastRemoteObject implements LireToutUnTexte {
	final static long serialVersionUID = 1;
	private String Stexte = "";
	private BreakIterator bi;
	
	public LireToutUnTexteServeur() throws java.rmi.RemoteException {
	}
	
	/** lecture d'un fichier texte dans la cha�ne sTexte 
	 * @param ft nom du fichier 
	 */
	public void Initialisation(String ft) {
		String ligne;
		try {
			FileReader fr = new FileReader(ft);
			BufferedReader br = new BufferedReader(fr);
			while ((ligne=br.readLine()) != null) {
				Stexte = Stexte.concat(ligne);
			}
			br.close();
		// segmentation en mots
			bi = BreakIterator.getWordInstance();
			bi.setText(Stexte);
		} 
		catch (IOException e) { e.printStackTrace(); } 
	}
	
	/** Recherche du nombre d'occurrences de s dans sTexte
	 * @param s cha�ne cherch�e
	 * @return nombre d'occurrences 
	 */
	public int Chercher(String s) throws java.rmi.RemoteException {
		int compteur = 0, i = 0;
		while ((i = Stexte.indexOf(s, i)) != -1) {
			compteur++;
			i += s.length();
		}
		return compteur;
	}
	
	/**
	 * 
	 * @param indice
	 * @param offset
	 * @return
	 */
	private String getMot(int indice, int offset) {
		int debut, fin;
		
		if (offset > 0)  {
			bi.following(indice);
			bi.next(2*offset-1);
			debut = bi.current();
			fin = bi.next();
		}
		else {
			bi.preceding(indice+1);
			bi.next(2*offset+1);
			fin = bi.current();
			debut = bi.previous();
		}
		
		return Stexte.substring(debut, fin);
	}
	
	/** Affichage du contexte des occurrences de s dans sTexte
	 * @param s cha�ne cherch�e
	 * @param taille taille du contexte
	 */
	public void ChercherVoir(String s, int taille) throws java.rmi.RemoteException {
		int i = 0;
		while ((i = Stexte.indexOf(s, i)) != -1) {
			for (int j = -taille; j <= taille;j++) 
				System.out.print(getMot(i, j) + " ");
			System.out.println();
			i += s.length();
		}
		return;
	}
	
}
