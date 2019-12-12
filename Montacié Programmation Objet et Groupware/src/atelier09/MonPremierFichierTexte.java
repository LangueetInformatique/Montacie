package atelier09;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;


public class MonPremierFichierTexte {

	public static void main(String[] args) {
		String noms[] = {"Montacié","Lejeune","Devillers"};
		String nfich = "src/atelier09/Nom.txt";
		
		try {
			PrintWriter pr = new PrintWriter(new File(nfich));
			for (int i = 0; i < noms.length;i++) 
					pr.println(noms[i]);
		pr.close();
		System.out.println(verifier(nfich, noms));
		} 
		catch (IOException e) { e.printStackTrace(); }
	}
	
	public static boolean verifier(String nfich, String[] noms) {
		return true;
		
	}

}
