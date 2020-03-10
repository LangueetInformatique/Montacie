/*
 * Créé le 18 avr. 2006
 *
 * Pour changer le modèle de ce fichier généré, allez à :
 * Fenêtre&gt;Préférences&gt;Java&gt;Génération de code&gt;Code et commentaires
 */
package cours06;

public class testEnvoiMessage {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		EnvoiMessage c = new EnvoiMessage("mailhost", 25);
		String sujet = "test d'envoi d'un message";
		String message = "cours du 25 avril 2006";
		String expediteur = "Claude.Montacie@paris4.sorbonne.fr";
		String destinataire = "ilgii1@laposte.net";
		c.envoie(expediteur, destinataire, sujet , message);
		c.fin();
	}

}
