package cours06;

import java.io.*;
import java.net.*;

public class LectureMessage {
	private BufferedReader from = null;
	private PrintWriter to = null;
	private Socket s;
	
	/** Cr�ation d'un connexion TCP avec le port du MDA 
	 * 
	 * @param POP nom du MDA
	 * @param port port MDA (en g�n�ral 110)
	 */
	public LectureMessage(String POP, int port)
	{
		// cr�ation de la socket
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
		//InetSocketAddress saddr1 = new InetSocketAddress(MUA, port);
		//s.bind(saddr1);
		
		//	adresse de la machine distante
		InetAddress MTA = InetAddress.getByName(POP);
		InetSocketAddress saddr2 = new InetSocketAddress(MTA, port);
		
		// demande de connexion
		s.connect(saddr2, 500);
		System.out.println("Connexion �tablie entre " +
				s.getLocalSocketAddress() + " et " +
				s.getRemoteSocketAddress());
	    }
		catch (IOException exp){
			System.out.println("erreur d'ouverture");
			}
	
	// Cr�ation des flots
	try {
	from = new BufferedReader(new InputStreamReader(s.getInputStream()));
	to = new PrintWriter(s.getOutputStream(), true);
	}
	catch (IOException exp){
		System.out.println("erreur de cr�ation des flots");
		}
	}
	
	/** passage dans l'�tat transaction d'un utilisateur donn�
	 * @param user nom de l'utilisateur
	 * @param password mot de passe de l'utilisateur
	 */
	void transaction (String user, String password) {
		String sMUA, sMTA;
		
		try {
			sMTA = from.readLine(); System.err.println(sMTA);
			sMUA = "USER " + user;
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
			sMUA = "PASS " + password;
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
			System.err.println("Passage dans l'�tat transaction");
		}
		catch (Exception e) {
			System.err.println(e);
		}
	}

	/** nombre de messages d'un utilisateur donn�
	 * @param user nom de l'utilisateur 
	 * @param password mot de passe de l'utilisateur
	 * @return nombre de messages
	 */
	int nbMessages(String user, String password) {
		String sMUA, sMTA;
		
		int nMessages = -1;
		transaction(user, password);
		try {
			sMUA = "LIST";
			System.err.print(sMUA + " "); to.println(sMUA); 
			sMTA = from.readLine(); System.err.println(sMTA);
			do {
				sMTA = from.readLine(); System.err.println(sMTA);
				nMessages++;
			} while (!sMTA.equals("."));
		} catch (Exception e) {
			System.err.println(e);
		}
			
			return nMessages++;
		}
		
	/** lecture d'un message donn� d'un utilisateur donn�
	 * @param im index du message
	 * @param user nom de l'utilisateur 
	 * @param password mot de passe de l'utilisateur
	 */
	String lire(int im, String user, String password) {
		String str = null, message = null;
		transaction(user, password);
		try {
			to.println("RETR " + im);
			str = from.readLine(); System.err.println(str);
			do  { message += from.readLine() + "\n"; }
			while (!message.endsWith("\n.\n"));
		} catch (Exception e) {
			System.err.println(e);
		}
		return message;
	}
	
	/** destruction d'un message donn� d'un utilisateur donn�
	 * @param im index du message
	 * @param user nom de l'utilisateur 
	 * @param password mot de passe de l'utilisateur
	 */
	void detruire(int im, String user, String password) {
		String str = null;
		transaction(user, password);
		try {
			to.println("DELE " + im);
			str = from.readLine(); System.err.println(str);
		} catch (Exception e) {
			System.err.println(e);
		}
		return;
	}
	
	/** fermeture de la connexion */
	public void fin() {
		try { to.println("QUIT"); s.close(); }
		catch( Exception e) {System.out.println("Erreur r�seau");}	
	}

}
