/**
 * 
 */
package atelier06;

/**
 * @author tyratron
 *
 */
public class Chat extends Felin implements Domesticable {

	private String nom;
	/**
	 * @param type
	 */
	public Chat(String nom) {
		super("chats");
		domestiquer(nom);
	}
	
	/** presentation des caracteristiques du chat */
	public void presente() {
		super.presente();  // appel de la m�thode de la sur-classe
		System.out.println("et je m'appelle " + nom());
	}

	@Override
	public void domestiquer(String nom) {
		domestique = true;
		this.nom = nom;
	}

	@Override
	public String nom() {
		// TODO Auto-generated method stub
		return this.nom;
	}
	
	/** cri du chat */
	public void crie() {
		System.out.println("et je miaule");

	}

}
