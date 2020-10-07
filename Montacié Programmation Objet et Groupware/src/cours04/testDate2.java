package cours04;

public class testDate2 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Date2 heure = new Date2();
		heure.Afficher2();// Affichage de l'heure

		Date2 today = new Date2(24, 10, 2003);
		today.Afficher();// Affichage du jour et de l'heure
	}

}
