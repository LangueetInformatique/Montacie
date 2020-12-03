
package cours09;

import javax.swing.*;
import java.awt.Color;

public class testPanneauDessinSouris {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

 	JFrame fen = new JFrame("Panneau de dessin � la souris");
 	fen.setSize(380, 380);
 	fen.getContentPane().setBackground(Color.CYAN);  
 	PanneauDessinSouris p = new PanneauDessinSouris();
 	p.setForeground (Color.MAGENTA);
 	fen.getContentPane().add(p);  
 	fen.setVisible(true);
}
}


