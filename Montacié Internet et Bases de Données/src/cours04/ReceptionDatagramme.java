
package cours04;

import java.io.IOException;
import java.net.*;

public class ReceptionDatagramme {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
//		 cr�ation de la socket
		DatagramSocket ds = null;
		int port = 32006;
		try {
			ds = new DatagramSocket(port);
		}
	    catch (SocketException exp){
			System.out.println("erreur de cr�ation de socket");
			}
		
		// r�ception du datagramme
		try {
		byte b[] = new byte [1024];
		DatagramPacket dp = new DatagramPacket(b, b.length);
		ds.receive(dp);
		InetSocketAddress saddr = (InetSocketAddress)dp.getSocketAddress(); 
		System.out.println("datagramme en provenance de " + saddr.toString());
		System.out.println(new String(b, 0, dp.getLength()));
		}
	    catch (SocketException exp){
			System.out.println("erreur de cr�ation paquet");
			}
		    catch (IOException exp){
			System.out.println("erreur de sortie");
			}
	}

}
