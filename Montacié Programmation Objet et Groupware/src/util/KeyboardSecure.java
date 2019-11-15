package util;  import java.io.*;
/**
 * Biblioth�que des entr�es s�curis�es clavier
 * Lecture robuste des variables de type natif
 * (byte, short, int, float, double, char)
 * et de variables de type String
 * Toutes les m�thodes sont des m�thodes de classe
 */
public class KeyboardSecure {
	/**
	 * Lecture d'une ligne saisie au clavier
	 * @return 	La cha�ne de caract�res saisie au clavier
	 */
	private static String getLine() {
		String ligne_lue = null;
		try {
			InputStreamReader lecteur = new
								    InputStreamReader(System.in);
			BufferedReader entree = new BufferedReader(lecteur);
			ligne_lue = entree.readLine();
		} 
		catch (IOException e) { System.exit(0); }
		return ligne_lue;
}

	/**
	* Lecture d�une cha�ne de caract�res saisie au clavier
	* @param mess	Message d'invite d�entr�e au clavier
	* @return 	La cha�ne lue au clavier
	*/
	public static String getString(String mess) {
		System.out.print(mess);
		return getLine();
	}

	/**
	* Lecture d'un caract�re saisi au clavier
	* @param mess	Message d'invite � entrer un caract�re au clavier
	* @return 	Le caract�re lu au clavier
	*/
	public static char getChar(String mess) {
		System.out.print(mess);
		return getLine().charAt(0);
	}

	/**
	* Lecture robuste d'un int saisi au clavier
	* @param mess Message d'invite � entrer un int au clavier
	* @return l'int lu au clavier
	*/
	public static int getInt(String mess) {
		System.out.print(mess);
		int entier=Integer.MIN_VALUE;
		while (true) {
			try { entier = Integer.parseInt(getLine()); break; }
			catch (NumberFormatException e){ 
				System.out.println("Erreur de format...");
				System.out.print(mess); 
			}
		}
		return entier;
	}
	
	/**
	* Lecture robuste d'un float saisi au clavier
	* @param mess Message d'invite � entrer un float au clavier
	* @return le float lu au clavier
	*/
	public static float getFloat(String mess) {
		System.out.print(mess);
		float reel=Float.MIN_VALUE;
		while (true) {
			try { reel = Float.parseFloat(getLine()); break; }
			catch (NumberFormatException e){ 
				System.out.println("Erreur de format...");
				System.out.print(mess); 
			}
		}
		return reel;
	}
}