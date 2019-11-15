package cours06;

import java.io.*;
import util.Keyboard;

public class testEcrTxt {
	public static void main(String[] args) {
		try {
			File f = new File(Keyboard.getString("Nom du fichier � �crire : "));
			PrintWriter pr = new PrintWriter(f);
			pr.print("Hello, ");
			pr.print("you...");
			pr.close();
			System.out.println("Fin d'�criture fichier");
		} 
		catch (IOException e) { e.printStackTrace(); }
	} 
}
