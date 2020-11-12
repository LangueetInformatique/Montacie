package cours05;

public class test2Tableau {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Tableau phrase = new Tableau(2);
		String mot;
		try {
			phrase.put(0, "le"); mot = phrase.get(0);System.out.println(mot);
			phrase.put(1, "livre"); mot = phrase.get(1); System.out.println(mot);
			phrase.put(2, "de"); mot = phrase.get(2); System.out.println(mot);
		}
		catch (IndexOutOfBoundsException e) {
			System.out.println("Reprise du contr�le d'ex�cution");
			e.printStackTrace();	
			System.out.println("Sortie de programme"); System.exit(0);
		}


	}

}
