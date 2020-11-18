package cours06;

import java.io.*;
import java.util.zip.*;
import util.Keyboard;

public class testEcrZip {
	public static void main(String[] args) {
		try {
			File f = new File(Keyboard.getString("Nom du fichier compress� : "));
			FileOutputStream fos = new FileOutputStream(f);
			DeflaterOutputStream dos = new DeflaterOutputStream(fos);
			DataOutputStream fdos = new DataOutputStream(dos);
			fdos
					.writeUTF("Le pr�sident de la Serbie-Mont�n�gro s'excuse pour la guerre en Bosnie.");
			fdos.writeUTF("Le Monde");
			fdos.close();
			System.out.println("Fin d'�criture de fichier");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
