package cours06; import java.io.*;

public class GestionFile {
	public static File findFirst(File f, String nomFichier) {
		File fres = null; int i; 
		File[] tf = f.listFiles(); 	// liste des fichiers du 							// r�pertoire
		for (i = 0;i < tf.length;i++) {
			fres = tf[i];
			if (fres.isDirectory() == true) {
				fres = findFirst(tf[i], nomFichier);
				if (fres != null) break; // sortie de boucle
			}
			else 
				if (fres.getName().equals(nomFichier) == true)
				break; // sortie de boucle
		}
		if (i == tf.length) return null; // fichier non trouv�
		else return fres; // fichier trouv�
	}
}

