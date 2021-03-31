
package cours08;

import java.io.*;
import java.net.*;

public class ReponseGet {
	private BufferedReader from = null;
	private PrintWriter to = null;
	private Socket s;
	
	/** Acceptation d'un connexion TCP avec l'UA 
	 * @param port port SA (en général 80)
	 */
	public ReponseGet(int port) {
		
		InetSocketAddress saddr = null;
		s = null;
		try {
			InetAddress addr = InetAddress.getLocalHost();
			saddr = new InetSocketAddress(addr, port);
		}
	    catch (UnknownHostException exp){
	    	System.out.println("machine inconnue");
	    }
		
		try {
        // création d'un écouteur de connexion
		ServerSocket ss = new ServerSocket();
		// attachement
		ss.bind(saddr);
		// acceptation de la connexion
		s = ss.accept();
		System.out.println("Connexion établie entre " +
				s.getLocalSocketAddress() + " et " +
				s.getRemoteSocketAddress());

		}
		catch (IOException exp){
			System.out.println("erreur d'ouvertue");
			}
		
//		 Création des flots
		try {
		from = new BufferedReader(new InputStreamReader(s.getInputStream()));
		to = new PrintWriter(s.getOutputStream(), true);
		}
		catch (IOException exp){
			System.out.println("erreur de création des flots");
		}
	}
	
	/** fermeture de la connexion */
	public void fin() {
		try { s.close(); }
		catch( Exception e) {System.out.println("Erreur réseau");}	
	}
	
	/** Reponse RGET 
	 * @param rep répertoire racine du site
	 */
	void RGet (String rep) {
		String sUA, sSA;
		
		try {
//			 lecture de l'entéte et recherche de la ressource demandée
			sUA = from.readLine(); System.err.println(sUA);
			String[] tag = sUA.split(" ");
			if ((tag[0].equals("GET")) == false) return;
			File fin= new File(tag[1].replaceFirst("/", rep));
			if (fin.exists() == false) {
				sSA = " HTTP/1.1 404 NOT FOUND\n"; 
				System.err.print(sSA + " "); to.println(sSA);
				return;
			}
			do {
				sUA = from.readLine(); System.err.println(sUA);
			} while (sUA.length() != 0);
			
			FileReader fr = new FileReader(fin);
			long taille = fin.length();
			sSA = " HTTP/1.1 200 OK";
			System.err.println(sSA); to.println(sSA);
			sSA = "Content-Length: " + taille +"\n";
			System.err.println(sSA); to.println(sSA);
			// lecture du fichier et creation du corps
			int n = 0; int c;
			do {
				c = fr.read(); to.write(c); n++;
			} while (n < taille);
			fr.close();
			to.println();
		}
		catch (Exception e) {
			System.err.println(e);
		}
	}
		
}

