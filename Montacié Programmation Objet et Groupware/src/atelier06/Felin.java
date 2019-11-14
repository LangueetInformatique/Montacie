package atelier06;

/** Création et gestion de félins */
public class Felin extends Animal {
// ajout d'attributs propres à la sous-classe
	protected boolean domestique = false;

	/**
	 * le constructeur de Félins fait appel au constructeur de la sur-classe Animal
	 */
	public Felin(String type) { // les félins ont 4 pattes
		super(type, 4); // appel du construction de la super-classe
	}					// obligatoire en cas de constructeur non-vide

	/** présentation des caractéristiques du félin */
	public void presente() {
		super.presente();  // appel de la méthode de la sur-classe
		String etat = (domestique) ? "domestique" : "sauvage";
		System.out.println("je suis vraiment un animal " + etat);
	}

	/** cri du félin */
	public void crie() {
		System.out.println("et je rugis");

	}
}