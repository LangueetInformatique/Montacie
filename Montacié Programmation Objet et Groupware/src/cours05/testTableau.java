package cours05;

public class testTableau {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Tableau phrase = new Tableau(2);
		String mot;        
		phrase.put(0, "le");
		mot = phrase.get(0); System.out.println(mot); 
		phrase.put(1, "livre"); 
		mot = phrase.get(1); System.out.println(mot); 
		phrase.put(2, "de");	
		mot = phrase.get(2); System.out.println(mot);       
	}


}
