/*
 * Créé le 15 oct. 2003
 *
 * Pour changer le modèle de ce fichier généré, allez à :
 * Fenêtre&gt;Préférences&gt;Java&gt;Génération de code&gt;Code et commentaires
 */
package util;

import java.io.*;
import java.util.*;


/**
 * @author montacie
 *
 * Pour changer le modèle de ce commentaire de type généré, allez à :
 * Fenêtre&gt;Préférences&gt;Java&gt;Génération de code&gt;Code et commentaires
 */
public class Keyboard {
	private static String[] Lire (String mess) {
			System.out.println(mess);
			String ligne_lue = null;
			try {
				InputStreamReader lecteur = new InputStreamReader(System.in);
				BufferedReader entree = new BufferedReader(lecteur);
				ligne_lue = entree.readLine();
			} catch (IOException err) {System.exit(0); }
        
			// Calcul du nombre de mots
        
			char oldcar = ' ', car;
			int nbMots = 0;
			for (int i = 0;i < ligne_lue.length();i++) {
				car = ligne_lue.charAt(i);
				if ((Character.isWhitespace(car) == false) && (Character.isWhitespace(oldcar) == true)) 
					nbMots++;
				oldcar = car;
			}
          
			String[] mots = new String[nbMots];
			StringTokenizer st = new StringTokenizer(ligne_lue);
			int j = 0;
			while (st.hasMoreTokens() == true) 
				mots[j++] = st.nextToken();
     

			return mots;
		}
		
	public static boolean getBoolean(String mess) {
			String mots[] = Lire(mess);
			return(Boolean.valueOf(mots[0]).booleanValue());
		}
		
	public static char getChar(String mess) {
			String mots[] = Lire(mess);
			return(mots[0].charAt(0));
		}
		
	public static int getInt(String mess) {
			String mots[] = Lire(mess);
			return(Integer.parseInt(mots[0]));
		}
	
	public static String getLigne(String mess) {
		System.out.println(mess);
		String ligne_lue = null;
		try {
			InputStreamReader lecteur = new InputStreamReader(System.in);
			BufferedReader entree = new BufferedReader(lecteur);
			ligne_lue = entree.readLine();
		} catch (IOException err) {System.exit(0); }
		return(ligne_lue);
	}
		
	public static String getString(String mess) {
		String mots[] = Lire(mess);
		return(mots[0]);
	}
	
	public static float getFloat(String mess) {
		String mots[] = Lire(mess);
		return(Float.parseFloat(mots[0]));
	}
	
	public static double getDouble(String mess) {
		String mots[] = Lire(mess);
		return(Double.parseDouble(mots[0]));
	}


}
