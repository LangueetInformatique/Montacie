
package cours05;

import java.io.*;
import java.net.*;
import java.util.Date;

public class EcouteurTCP implements Runnable {

	BufferedReader br = null;
	PrintWriter pw = null;

	public EcouteurTCP(Socket s) {
		try {
			br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			pw = new PrintWriter(s.getOutputStream(), true);
		} catch (IOException exp) {
			System.out.println("errreur de creation des flots");
		}

		new Thread(this).start();
	}

	public void run() {
		Date d = new Date();

		// Communication
		try {
			String ligne = br.readLine();
			System.out.println(ligne);

			pw.println("bienvenue sur le serveur " + d.toString());
		} catch (IOException exp) {
			System.out.println("erreur d'entee-sortie");
		}
	}

}
