package cours07;

public class testCompare {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Raccord de m�thode auto-g�n�r�
		String s1 = new String("la fille du roi zoulou Goodwill Zwelithini") ;
		String s2 = new String("comme conseiller du roi zoulou Cetawayo.") ;
		    
		System.out.println(s1.endsWith("."));
			// false

		System.out.println(s2.endsWith("."));
			// true
		    
		System.out.println(s1.indexOf("roi zoulou"));
			// 12

		System.out.println(s2.indexOf("roi zoulou"));
			// 20
		    
		System.out.println(s1.regionMatches(true, 12, s2, 20, 10));
			// true


	}

}
