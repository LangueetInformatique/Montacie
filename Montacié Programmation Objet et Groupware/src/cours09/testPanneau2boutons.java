
package cours09;

import javax.swing.*;
public class testPanneau2boutons {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Raccord de methode auto-genere
		
//		Declaration de la JFrame
		 JFrame fen = new JFrame("Panneau a 2 boutons cliquables"); 
		 fen.setSize(380, 180); 
		 Panneau2Boutons p = new Panneau2Boutons();
		 fen.getContentPane().add(p);  

//			Affichage de la JFrame et de son contenu
		 fen.setVisible(true);

	}

}
