package atelier09;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.FileReader;
import util.Keyboard;

public class MonPremierFichierTexte {

	public static void main(String[] args) {
		String noms[] = { "Montacie", "Eyharabide", "Devillers" };
		String nfich = "src/atelier09/Nom.txt";

		try {
			PrintWriter pr = new PrintWriter(new File(nfich));
			for (int i = 0; i < noms.length; i++)
				pr.println(noms[i]);
			pr.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	

}
