package cours07;

import java.io.*;

public class testConstructeurs {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String s1, s2, s3 = null;
		// TODO Raccord de m�thode auto-g�n�r�
		byte[] tb = {112, 114, 111, 112, 114, 105, -23, 116, -23, 115, 32, 100, 101, 115, 32, 99, 111, 110, 115, 116, 114, 117, 99, 116, 101, 117, 114, 115};
		s1 = new String(tb); System.out.println(s1); 
			// propri�t�s des constructeurs
		s2 = new String(tb, 11, 3); System.out.println(s2); 
			// des        

		try { s3 = new String(tb, "ISO-8859-5"); } 
		catch (IOException e) {} System.out.println(s3); 
			// propri?t?s des constructeurs

		char[] tc = {'p', 'r', 'o', 'p', 'r', 'i', '�', 't', '�', 's'}; 
		String s4 = new String(tc); System.out.println(s4);
			//   propri�t�s
		String s5 = new String(tc, 6, 3); System.out.println(s5);
			//   �t�
		String s6 = new String(s4 + " " + s2); System.out.println(s6);
			//   propri�t�s des


	}

}
