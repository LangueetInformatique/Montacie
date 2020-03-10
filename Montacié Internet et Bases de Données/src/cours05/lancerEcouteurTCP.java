package cours05;

import java.io.*;
import java.net.*;

public class lancerEcouteurTCP {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int port = 32006;
		InetSocketAddress saddr = null;
		Socket s = null;
		try {
			InetAddress addr = InetAddress.getLocalHost();
			saddr = new InetSocketAddress(addr, port);
		}
	    catch (UnknownHostException exp){
	    	System.out.println("machine inconnue");
	    }
		
		try {
        // creation d'un ecouteur de connexion
		ServerSocket ss = new ServerSocket();
		// attachement
		ss.bind(saddr);
		// acceptation de la connexion
		while (true) {
			s = ss.accept();
			System.out.println("Connexion �tablie entre " +
					s.getLocalSocketAddress() + " et " +
					s.getRemoteSocketAddress());
			new EcouteurTCP(s);
		}
		}
		catch (IOException exp){
			System.out.println("erreur d'ouvertue");
			}
		
	}

}
