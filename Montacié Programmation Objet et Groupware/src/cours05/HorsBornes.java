package cours05;

public class HorsBornes extends Exception {
	final static long serialVersionUID = 1;
	/**
 	 * Cr�ation d'une nouvelle instance de la classe HorsBorne
 	 * @param i indice hors bornes
 	 */
	public HorsBornes(int i) {
		super("Indice " + i + " hors bornes, recommencez...");
	}    
}
