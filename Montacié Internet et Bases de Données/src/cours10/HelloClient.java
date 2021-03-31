package cours10;

import java.rmi.registry.*;

public class HelloClient {
  public static void main(String args[]) {
	  int port = 12536;    
	  String host = "lili";
    try {
    	
      Registry r = LocateRegistry.getRegistry(host, port);
      
      // R�cup�ration d'un stub sur l'objet serveur.
      Hello obj = (Hello) r.lookup("//lili:12535/Hello");
      // Appel d'une m�thode sur l'objet distant.
      String msg = obj.sayHello();
      // Impression du message.
      System.out.println(msg);
    } catch (Exception exc) { }
  }
}
