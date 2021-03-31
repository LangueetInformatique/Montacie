package cours05;

public class testCompteurs {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		// lancement des compteurs
		Compteur[] pa = new Compteur[5];
		for (int i = 0; i < pa.length; i++) {
			pa[i] = new Compteur(10 * (i + 1));
			pa[i].start();
		}

	}

}
