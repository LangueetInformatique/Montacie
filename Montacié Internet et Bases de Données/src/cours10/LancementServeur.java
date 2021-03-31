/*
 * Cr�� le 5 avr. 07
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours10;

import java.net.InetAddress;
import java.rmi.registry.*;

public class LancementServeur {
	public static void main(String args[]) {
	    int port = 12537;    
	  
	    try {
	    	String host = InetAddress.getLocalHost().getHostName();
	    	  
	    	// Cr�ation du serveur de noms - rmiregistry
	    	Registry r = LocateRegistry.createRegistry(port);

	    	// Cr�ation d�une instance des objets serveur
	    	HelloServeur o1 = new HelloServeur();
	    	LireToutUnTexteServeur o2 = new LireToutUnTexteServeur();

	    	// Inscription des serveurs Hello et Lire
	    	r.rebind("//"+host+":"+port+"/Hello", o1);
	    	r.rebind("//"+host+":"+port+"/Lire", o2);

	    	// Liste des serveurs inscrits
	    	String s[] = r.list();
	    	for (int i = 0;i < s.length;i++) System.out.println(s[i]);
	       
	    } catch (Exception exc) {}
	}

}
