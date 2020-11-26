package atelier09;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.util.zip.DeflaterOutputStream;
import util.Keyboard;

public class Compresse {

	public static void main(String[] args) {
		try {
			String rep = "src/atelier09/";
			File fin = new File(rep + Keyboard.getString("Nom du fichier source à compresser : "));
			FileInputStream fis = new FileInputStream(fin);
			File fout = new File(rep + Keyboard.getString("Nom du fichier compressé : "));
			FileOutputStream fos = new FileOutputStream(fout);
			DeflaterOutputStream dos = new DeflaterOutputStream(fos);

			// calcul de la taille du fichier et copie
			long taille = fin.length();
			byte mem[] = new byte[(int) taille];
			fis.read(mem);
			dos.write(mem);

			fis.close();
			dos.close();
		}

		catch (EOFException e) {
			System.out.println("Fin de lecture de fichier");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
