package cours06;  import java.io.*;  import util.*;

public class testGestionFile {
	public static void main(String[] args) {
		String nR = Keyboard.getString("R�pertoire de recherche : "); 
		String nF = Keyboard.getString("Fichier � rechercher : "); 
		File fres = GestionFile.findFirst(new File(nR), nF);
		if (fres != null) {
			System.out.println("Chemin absolu du fichier : ");
			System.out.println(fres.getAbsolutePath());
		}
		else System.out.println("Aucune occurrence du fichier..."); 
	}
}

