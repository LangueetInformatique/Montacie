package atelier09;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;


public class MonPremierFichierTexte {

	public static void main(String[] args) {
		String noms[] = {"Montacié","Lejeune","Devillers"};
		
		try {
			PrintWriter pr = new PrintWriter(new File("src/atelier09/Nom.txt"));
			for (int i = 0; i < noms.length;i++) 
					pr.println(noms[i]);
		pr.close();
		} 
		catch (IOException e) { e.printStackTrace(); }

	}

}
