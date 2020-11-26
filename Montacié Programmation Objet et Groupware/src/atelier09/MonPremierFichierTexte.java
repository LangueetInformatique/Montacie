package atelier09;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

import util.Keyboard;

public class MonPremierFichierTexte {
	/*
	Exercice 1 : Créer la classe exécutable MonPremierFichierTexte 
	qui écrit dans le fichier texte « Nom.txt » les noms des membres du groupe. 
	*/

	public static void main (String[] args) {
		String ligne;
		String nfich = "src/atelier09/Nom.txt";
		try {
			File f = new File(nfich);
			
			PrintWriter pr = new PrintWriter(f);
			pr.println("Morgann");
			pr.println("Julien");
			pr.println("Mustapha");
			pr.println("Chenwangli");
			pr.println("Ana");
			pr.println("Joyce");
			
			pr.close();
			System.out.println("Fin d'écriture fichier");
		
	}
		catch (IOException e) {e.printStackTrace(); }
}
}