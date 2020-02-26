
package cours04;

import java.io.*;
import java.net.*;

public class DemandeConnexion {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		// cr�ation de la socket
		Socket s = new Socket();
		InetAddress addr1 = null;
		int port1 = 32005, port2 = 32006;
		try {
			addr1 = InetAddress.getLocalHost();
		}
	    catch (UnknownHostException exp){
		System.out.println("machine inconnue");
		}
		
	    try {
	    	
		// attachement
		InetSocketAddress saddr1 = new InetSocketAddress(addr1, port1);
		s.bind(saddr1);
		
		//	adresse de la machine distante
		InetAddress addr2 = InetAddress.getByName("192.168.1.102");
		InetSocketAddress saddr2 = new InetSocketAddress(addr2, port2);
		
		// demande de connexion
		s.connect(saddr2);
		System.out.println("Connexion �tablie entre " +
				s.getLocalSocketAddress() + " et " +
				s.getRemoteSocketAddress());
	    }
		catch (IOException exp){
			System.out.println("erreur d'ouverture");
			}
	   
	
	// Cr�ation des flots
	BufferedReader br = null;
	PrintWriter pw = null;
	try {
	br = new BufferedReader(new InputStreamReader(s.getInputStream()));
	pw = new PrintWriter(s.getOutputStream(), true);
	}
	catch (IOException exp){
		System.out.println("erreur de cr�ation des flots");
		}
	
	// Communication
	try {
	pw.println("d�but de la communication");
	String ligne = br.readLine();
	System.out.println(ligne);
	}
	catch (IOException exp){
		System.out.println("erreur d'ent�e-sortie");
		}
	}

}
