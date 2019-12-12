package atelier09;

import java.io.File;
import util.Keyboard;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class Copie {

	public static void main(String[] args) {
		

		try {
		File fin = new File(Keyboard.getString("fichier source : "));
		FileInputStream fis = new FileInputStream(fin);
		FileOutputStream fos =  new FileOutputStream(new File(Keyboard.getString("fichier cible : ")));
		
		byte[] b = new byte[(int)fin.length()];
		fis.read(b);
		fos.write(b);
		
		
		fis.close();
		fos.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
