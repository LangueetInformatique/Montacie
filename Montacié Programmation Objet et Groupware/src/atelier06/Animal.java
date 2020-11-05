package atelier06;

/** Creation et gestion d'animaux */
public abstract class Animal {
	private String espece;
	private int nb_pattes = 0;

	/**
	 * creation d'une nouvelle instance de la classe Animal
	 * 
	 * @param type   nom de l'espece
	 * @param pattes nombre de pattes
	 */
	public Animal(String type, int pattes) {
		espece = type;
		nb_pattes = pattes;
	}

	/** presentation des caract�ristiques de l'animal */
	public void presente() {
		System.out.println("je suis un representant de l'espece des " + espece + " et j'ai " + nb_pattes + " pattes");
	}

	/** cri de l'animal */
	public abstract void crie();
}