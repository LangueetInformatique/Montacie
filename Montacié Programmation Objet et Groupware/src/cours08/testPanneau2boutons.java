/*
 * Cr�� le 4 janv. 2006
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours08;

import javax.swing.*;
public class testPanneau2boutons {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Raccord de m�thode auto-g�n�r�
		
//		D�claration de la JFrame
		 JFrame fen = new JFrame("Panneau à 2 boutons cliquables"); 
		 fen.setSize(380, 180); 
		 Panneau2Boutons p = new Panneau2Boutons();
		 fen.getContentPane().add(p);  

//			Affichage de la JFrame et de son contenu
		 fen.setVisible(true);

	}

}
