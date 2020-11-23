package cours07;

public class testStrBuffer {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Raccord de m�thode auto-g�n�r�
		String s1= new String("la fille du roi zoulou Goodwill Zwelithini   ");
		StringBuffer sb1 = new StringBuffer(s1);
		int i;
		        
		for (i=0;i < sb1.length();i++) {
			char car = sb1.charAt(i);
			if ((car >= 'A') && (car <= 'Z')) {
				car += 'a' - 'A'; sb1.setCharAt(i, car); }
			} System.out.println(sb1 + ".");
			// la fille du roi zoulou goodwill zwelithini   .        

		i = sb1.length() - 1;
		while ((i >= 0) && (sb1.charAt(i)==' ')) sb1.deleteCharAt(i--);
		sb1.append("."); System.out.println(sb1);
			// la fille du roi zoulou goodwill zwelithini.       

		sb1.replace(0, 8,  "le fils"); System.out.println(sb1);
			// le fils du roi zoulou goodwill zwelithini.

	}

}
