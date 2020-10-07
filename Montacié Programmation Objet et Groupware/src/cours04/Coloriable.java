/*
 * Cr�� le 31 oct. 2003
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours04;

/** gestion de la couleur d'une forme g�om�trique
  */
public interface Coloriable {
    /** liste des couleurs autoris�es */    
    static String[] couleurs = {"rouge","orange","jaune","vert","bleu","violet"};

    /** modification de la couleur d'une forme g�om�trique
     * @param co nouvelle couleur
     */    
    public abstract void changerCouleur(String co);
}

