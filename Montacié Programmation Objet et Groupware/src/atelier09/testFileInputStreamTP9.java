package atelier09;

import java.io.IOException;

public class testFileInputStreamTP9 {

	public static void main (String[] args) {
		try {
		FileInputStreamTP9 fis9 = new FileInputStreamTP9("src/atelier09/Nom.txt");
		int c;
		while ((c=fis9.read()) != -1)
			System.out.println(c);

	
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	

}
