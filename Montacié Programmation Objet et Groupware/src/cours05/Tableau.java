package cours05;

public class Tableau {
	protected String[] tab_;
	/** Cr�ation d'une nouvelle instance de la classe Tableau
	 * @param n taille du tableau */
	public Tableau(int n) {
		tab_ = new String[n];
		}
	/** lecture d'un �l�ment du tableau
	 * @param i indice du tableau
	 * @return �lement */    
	public String get(int i) {
		return(tab_[i]);
		}
	/** �criture d'un �l�ment dans le tableau
	 * @param i indice du tableau
	 * @param mot �l�ment � �crire */    
	public void put(int i, String mot) {
		tab_[i] = mot;
		} 
	}

