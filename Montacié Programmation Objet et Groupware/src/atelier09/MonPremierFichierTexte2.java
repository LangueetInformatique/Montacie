package atelier09;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.FileReader;
import util.Keyboard;

public class MonPremierFichierTexte2 {
	

	public static void main(String[] args) {
		String noms[] = { "Morgann", "Julien", "Mustapha","Chenwangli", "Ana","Joyce"};
		String nfich = "src/atelier09/Nom.txt";

		try {
			PrintWriter pr = new PrintWriter(new File(nfich));
			for (int i = 0; i < noms.length; i++)
				pr.println(noms[i]);
			pr.close();
			Keyboard.getString("verification faite");
			System.out.println(verifier(nfich, noms));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static boolean verifier(String nfich, String[] noms) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader(new File(nfich)));
		for (int i = 0; i < noms.length; i++) {
			String nom = br.readLine();
			System.out.println(nom);
			if ((nom.equals(noms[i])) == false) {
				br.close();
				return false;
			}
		}
		br.close();
		return true;

	}

}
