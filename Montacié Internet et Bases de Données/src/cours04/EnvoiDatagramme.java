
package cours04;

import java.io.IOException;
import java.net.*;

public class EnvoiDatagramme {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// cr�ation de la socket
		DatagramSocket ds = null;
		int port = 32006;
		try {
			ds = new DatagramSocket();
		}
	    catch (SocketException exp){
			System.out.println("erreur de cr�ation de socket");
			}
	    // adresse de la machine distante
	    InetSocketAddress saddr = null;
		try {
			InetAddress addr = InetAddress.getByName("192.168.1.102");
			saddr = new InetSocketAddress(addr, port);
			}
		catch (UnknownHostException exp){
			System.out.println("machine inconnue");
			}
		// construction et envoi du datagramme
		try {
		String s = "debut de la communication";
		byte[] b = s.getBytes();
		DatagramPacket dp = new DatagramPacket(b, b.length, saddr );
		ds.send(dp);}
	    catch (SocketException exp){
			System.out.println("erreur de cr�ation paquet");
			}
		    catch (IOException exp){
			System.out.println("erreur de sortie");
			}
	}

}
