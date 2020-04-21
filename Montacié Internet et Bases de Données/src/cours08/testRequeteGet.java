
package cours08;


public class testRequeteGet {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		// Etablissement de la connexion
		RequeteGet p = new RequeteGet("www.linux-france.org", 80);
		// Envoi de la requete et lecture de la reponse
		p.Get("/prj/edu/archinet/systeme/ch16.html", "www.linux-france.org", "ch16.html");
		// fermeture de la connexion
		p.fin(); 

	}

}

