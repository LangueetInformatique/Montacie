package cours06;  import util.*;
/** Driver de test de la biblioth�que KeyboardSecure */
public class testLectureRobuste {

	public static void main(String[] args) {
		String ligne = KeyboardSecure.getString("Lecture d'une ligne: ");
		System.out.println("Ligne lue au clavier : " + ligne);
	
		char caractere = KeyboardSecure.getChar("Lecture d'un caract�re : ");
		System.out.println("Caract�re lu au clavier : " + caractere);
		
		int entier = KeyboardSecure.getInt("Entier : ");
		System.out.println("Entier lu au clavier : " + entier);
		
		float flottant = KeyboardSecure.getFloat("Flottant : ");
		System.out.println("Flottant lu au clavier : " + flottant);		
	}
}
