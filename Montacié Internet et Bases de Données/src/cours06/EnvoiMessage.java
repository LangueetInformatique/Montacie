package cours06;

import java.net.*;
import java.io.*;

/**
 * @author diam
 * 
 */
public class EnvoiMessage
{
	private BufferedReader from = null;
	private PrintWriter to = null;
	private Socket s;
	
	/** Création d'un connexion TCP avec le port du MTA 
	 * 
	 * @param SMTP nom du MTA
	 * @param port port du MTA (en général 25)
	 */
	public EnvoiMessage(String SMTP, int port)
	{
		// création de la socket
		s = new Socket();
		InetAddress MUA = null;
		try {
			MUA = InetAddress.getLocalHost();
		}
	    catch (UnknownHostException exp){
		System.out.println("machine inconnue");
		}
		
	    try {
	    	
		// attachement
		InetSocketAddress saddr1 = new InetSocketAddress(MUA, port);
		s.bind(saddr1);
		
		//	adresse de la machine distante
		InetAddress MTA = InetAddress.getByName(SMTP);
		InetSocketAddress saddr2 = new InetSocketAddress(MTA, port);
		
		// demande de connexion
		s.connect(saddr2);
		System.out.println("Connexion établie entre " +
				s.getLocalSocketAddress() + " et " +
				s.getRemoteSocketAddress());
	    }
		catch (IOException exp){
			System.out.println("erreur d'ouverture");
			}
	
	// Création des flots
	try {
	from = new BufferedReader(new InputStreamReader(s.getInputStream()));
	to = new PrintWriter(s.getOutputStream(), true);
	}
	catch (IOException exp){
		System.out.println("erreur de création des flots");
		}
	}
	
	/** Envoie du message au serveur de mail
	 * 
	 * @param origin adresse mail de l'expéditeur
	 * @param dest adresse mail du destinataire
	 * @param message
	 */
	public void envoie(String in, String out, String sujet, String message)
	{
	String sMUA, sMTA;
		
		try {
			sMTA = from.readLine(); System.err.println(sMTA);
			sMUA = "EHLO " + InetAddress.getLocalHost().getHostName();
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
			sMUA = "MAIL FROM:<"+in+">";
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
			sMUA = "RCPT TO:<"+out+">";
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
			sMUA = "DATA";
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
			sMUA = "Subject: " + sujet + "\n" + message + "\n.";
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
				
		}catch( Exception e) {System.out.println("Erreur réseau");}		
	}
	
	/** fermeture de la connexion */
	public void fin() {
		try {s.close(); }
		catch( Exception e) {System.out.println("Erreur réseau");}	
	}
	
	
}
