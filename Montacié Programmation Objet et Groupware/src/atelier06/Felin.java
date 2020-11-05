package atelier06;

/** Creation et gestion de felins */
public class Felin extends Animal {
// ajout d'attributs propres a la sous-classe
	protected boolean domestique = false;

	/**
	 * le constructeur de Felins fait appel au constructeur de la sur-classe Animal
	 */
	public Felin(String type) { // les felins ont 4 pattes
		
	}					

	/** presentation des caracteristiques du felin */
	public void presente() {
		
		String etat = (domestique) ? "domestique" : "sauvage";
		System.out.println("je suis vraiment un animal " + etat);
	}

	/** cri du felin */

}