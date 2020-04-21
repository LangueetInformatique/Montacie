
package cours08;

public class testReponseGet {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// Attente de la connexion
		ReponseGet p = new ReponseGet(80);
		// Reception de la requete et envoi de la reponse
		p.RGet("cours09/");
		// fermeture de la connexion
		p.fin(); 		

	}

}
