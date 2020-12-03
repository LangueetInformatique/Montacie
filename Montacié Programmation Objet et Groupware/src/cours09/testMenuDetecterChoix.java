
package cours09;

import javax.swing.JFrame;

public class testMenuDetecterChoix {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//		Declaration de la JFrame
		 JFrame fen = new JFrame("Detection du choix dans un menu"); 
		 fen.setSize(380, 180); 
		 String[] nomMenus = {"orange", "pomme", "banane","raisin"};
		 MenuDetecterChoix m = new MenuDetecterChoix(nomMenus);
		 fen.getContentPane().add(m);  

//			Affichage de la JFrame et de son contenu
		 fen.setVisible(true);

	}

}
