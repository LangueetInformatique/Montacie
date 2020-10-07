package cours03;

import util.Console;

public class BoucleConditionnelle {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Console c = new Console();

		// Boucle a posteriori
		int nbJets = 0, entier;
		do {
			entier = c.getInt("Entier ? ");
			if (entier < 0)
				c.println("pile");
			else
				c.println("face");
			nbJets++;
		} while (entier < 0);
		c.println("Face,gagn� en " + nbJets + " coup(s)");

		// Boucle a priori
		int nbEntiers = 0, cumul = 0;
		while ((entier = c.getInt("Entier ? ")) >= 0) {
			nbEntiers++;
			cumul += entier;
		}
		if (nbEntiers == 0)
			c.println("Pas d'entr�e d'entier positif");
		else
			c.println("Moyenne des entiers positifs : " + (float) cumul
					/ nbEntiers);

		// boucle it�rative
		int borne = 30;
		cumul = 0;
		for (int i = 0; i < borne; i++) {
			cumul += i;
		}
		c.println("Moyenne des " + borne
						+ " premiers entiers positifs : " + (float) cumul
						/ borne);

	}

}
