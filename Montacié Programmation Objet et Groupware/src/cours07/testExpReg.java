package cours07;

public class testExpReg {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Raccord de m�thode auto-g�n�r�
		String s1, s2, s3[], er1, er2, er3, er4;
		s1 = new String("la fille du roi zoulou Goodwill Zwelithini.");
		        
		er1 = new String("[a-zA-Z\\s\\.]*");
		System.out.println(er1 + " " + s1.matches(er1));
			// [a-zA-Z\s\.]* true
		        
		er2 = new String("((([a-z]*)|([A-Z][a-z]*))(\\s|\\.))*"); 
		System.out.println(er2 + " " + s1.matches(er2));
			// ((([a-z]*)|([A-Z][a-z]*))(\s|\.))* true

		er3 = new String("[A-Z][a-z]*");
		s2 = new String(s1.replaceAll(er3,"NomPropre ")); 
		System.out.println(er3 + " " + s2);
//		 [A-Z][a-z]* la fille du roi zoulou NomPropre  NomPropre .

		er4 = new String("\\s"); s3 = s1.split(er4); 
		System.out.println(er4 + " " + s3.length + " " );
		for (int i=0;i < s3.length;i++) System.out.print(s3[i] + " ,");
//		 \s 7 la ,fille ,du ,roi ,zoulou ,Goodwill ,Zwelithini. ,


	}

}
