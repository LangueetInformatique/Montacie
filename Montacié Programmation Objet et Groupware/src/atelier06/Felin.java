package atelier06;

/** Creation et gestion de felins */
public class Felin extends Animal {
// ajout d'attributs propres a la sous-classe
	protected boolean domestique = false;

	/**
	 * le constructeur de Felins fait appel au constructeur de la sur-classe Animal
	 */
	public Felin(String type) { // les felins ont 4 pattes
		super(type, 4); // appel du construction de la super-classe
	}					// obligatoire en cas de constructeur non-vide

	/** presentation des caracteristiques du felin */
	public void presente() {
		super.presente();  // appel de la methode de la sur-classe
		String etat = (domestique) ? "domestique" : "sauvage";
		System.out.println("je suis vraiment un animal " + etat);
	}

	/** cri du felin */
	public void crie() {
		System.out.println("et je rugis");

	}
}