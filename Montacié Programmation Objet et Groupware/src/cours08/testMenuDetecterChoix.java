/*
 * Cr�� le 5 janv. 2006
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours08;

import javax.swing.JFrame;

public class testMenuDetecterChoix {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//		D�claration de la JFrame
		 JFrame fen = new JFrame("D�tection du choix dans un menu"); 
		 fen.setSize(380, 180); 
		 String[] nomMenus = {"orange", "pomme", "banane","raisin"};
		 MenuDetecterChoix m = new MenuDetecterChoix(nomMenus);
		 fen.getContentPane().add(m);  

//			Affichage de la JFrame et de son contenu
		 fen.setVisible(true);

	}

}
