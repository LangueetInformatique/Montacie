package atelier10;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class LireToutUnTexte {
	private String Stexte;

	/**
	 * lecture d'un fichier texte dans la chaîne sTexte
	 * 
	 * @param ft descripteur du fichier
	 */
	public LireToutUnTexte(File ft) {

		String ligne = null;
		Stexte = "";

		try {
			BufferedReader br = new BufferedReader(new FileReader(ft));
			while ((ligne = br.readLine()) != null) {
				// System.out.println(ligne);
				Stexte += ligne + "\n";
			}

		}

		catch (IOException e) {
		}

	}

	/**
	 * Recherche du nombre d'occurences de s dans sTexte
	 * 
	 * @param s chaîne cherchée
	 * @return nombre d'occurences
	 */
	public int Chercher(String s) {
		int deb = -1, nOcc = 0;
		while ((deb = Stexte.indexOf(s, deb+1)) != -1)
			nOcc++;
		
		return nOcc;
	}

	/**
	 * Affichage du contexte des occurences de s dans sTexte
	 * 
	 * @param s      chaîne cherchée
	 * @param taille taille du contexte
	 */
	public void ChercherVoir(String s, int taille) {
	}
}