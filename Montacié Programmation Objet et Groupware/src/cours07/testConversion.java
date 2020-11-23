package cours07;

public class testConversion {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Raccord de m�thode auto-g�n�r�
		String s1 = new String("Le Norv�gien Sigurd Pettersen a remport�");           
		System.out.println(s1);
			// Le Norv�gien Sigurd Pettersen a remport�

		String s2 = new String(s1.toUpperCase()); 
		System.out.println(s2);
			// LE NORV�GIEN SIGURD PETTERSEN A REMPORT�

		String s3 = new String(s2.toLowerCase()); 
		System.out.println(s3);
			// le norv�gien sigurd pettersen a remport� 

		String s4 = new String(s3.concat(" la course ")); 
		System.out.println(s4 + ".");
			// le norv�gien sigurd pettersen a remport� la course .

		String s5 = new String(s4.trim()); 
		System.out.println(s5 + "."); 
			// le norv�gien sigurd pettersen a remport� la course.


	}

}
