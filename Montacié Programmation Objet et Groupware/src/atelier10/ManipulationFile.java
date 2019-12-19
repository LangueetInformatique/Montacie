package atelier10;

import java.io.File;

public class ManipulationFile {

	private File Repertoire;

	public ManipulationFile(File rep) {
		Repertoire = rep;
	}

	public void chercher(String regex) {
		chercher(Repertoire, regex);

	}

	private void chercher(File rep, String regex) {
		File fres = null;
		int i;
		File[] tf = rep.listFiles(); // liste des fichiers du // r�pertoire
		for (i = 0; i < tf.length; i++) {
			fres = tf[i];
			if (fres.getName().matches(regex))
				System.out.println(fres.getName());
			if (fres.isDirectory() == true) {
				chercher(tf[i], regex);
			}
		}

	}

	public static void main(String[] args) {

	}

}
