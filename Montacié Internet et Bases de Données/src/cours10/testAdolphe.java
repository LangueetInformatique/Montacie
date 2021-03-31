package cours10;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import util.Keyboard;

public class testAdolphe {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int port = 12537; 
		String host = "lili"; 
		String URL = "//"+host+":"+port+"/";
		 
		try {
			Registry r = LocateRegistry.getRegistry(host, port);
			// r�f�rence sur le talon de l'objet distant
			Hello h = (Hello) r.lookup(URL+"Hello");
			// appel � une m�thode distante
		    System.out.println(h.sayHello());
			LireToutUnTexte lt = (LireToutUnTexte) r.lookup(URL+"Lire");
			lt.Initialisation("cours07/adolphe.txt");
			String s = Keyboard.getString("mot � chercher? ");
			System.out.println("Il y a " + lt.Chercher(s) + " occurences de ce mot dans le texte");
	}
		catch (Exception exc) { }
	}
}
