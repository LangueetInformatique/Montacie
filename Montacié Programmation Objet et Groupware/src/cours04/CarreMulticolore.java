/*
 * Cr�� le 31 oct. 2003
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours04;

/** cr�ation et gestion de carr�s multicolores
  */
public class CarreMulticolore extends CarreRouge implements Coloriable {

    /** Cr�ation d'une nouvelle instance de la classe Carr�Multicolore
     * @param x c�t� du carr�
     * @param co couleur du carr�
     */
    public CarreMulticolore(float x, String co) {
        super(x);
        this.changerCouleur(co);
    }

	/** modification de la couleur d'un carr�
		 * @param co nouvelle couleur
		 */    
		public void changerCouleur(String co) {
			int i;
			for (i = 0;i < couleurs.length;i++)             // est-ce une couleur autoris�e ?
				if (co.equals(couleurs[i])== true) break; 
			if (i < couleurs.length) couleur = co;
		}
     
	}
