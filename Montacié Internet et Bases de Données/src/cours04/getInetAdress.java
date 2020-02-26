
package cours04;

import java.io.IOException;
import java.net.*;


public class getInetAdress {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		try{
			InetAddress  monAdresse = InetAddress.getByName("smtp.laposte.net");
			System.out.println(monAdresse.getHostName());
			System.out.println( monAdresse.getHostAddress());
			System.out.println( monAdresse.isAnyLocalAddress());
			System.out.println( monAdresse.isLoopbackAddress());
			System.out.println( monAdresse.isLinkLocalAddress());
			System.out.println( monAdresse.isReachable(100));

			} catch (UnknownHostException exp){
			System.out.println("machine inconnue");
			} catch (IOException e) {
				System.out.println("machine non atteignable");
			}
			


	}

}
