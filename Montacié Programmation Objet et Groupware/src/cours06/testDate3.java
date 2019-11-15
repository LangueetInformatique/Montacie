package cours06;

import java.io.*;
import util.Keyboard;

public class testDate3 {

	public static void main(String[] args) {
		File f = new File(Keyboard.getString("Nom du fichier � cr�er :"));
		
		Date3 today = new Date3(29, 11, 2007);
		Date3 fete = new Date3(14, 7, 2008);
		while (today.CompareTo(fete) == true) {
			today.Incrementer();
			today.Sauvegarder(f, true);
			System.out.println("date sauvegardee"); 
		}

	}

}
