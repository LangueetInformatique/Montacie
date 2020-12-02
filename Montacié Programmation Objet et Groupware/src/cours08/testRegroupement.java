package cours08;

import javax.swing.*;

import java.awt.*;


/**
 * @author montacie
 */
public class testRegroupement {

	public static void main(String[] args) {
		JFrame fen = new JFrame("Regroupement d'objets atomiques");
		fen.setSize(350, 100);
		JPanel p = new JPanel();
		fen.getContentPane().add(p);  
		p.setLayout(new GridLayout(1,3));
		
		JRadioButton rbt1 = new JRadioButton("bouton1"); p.add(rbt1); 
		JRadioButton rbt2 = new JRadioButton("bouton2"); p.add(rbt2); 
		JRadioButton rbt3 = new JRadioButton("bouton3"); p.add(rbt3); 
		ButtonGroup bg = new ButtonGroup();
		bg.add(rbt1); bg.add(rbt2); bg.add(rbt3);
		

        fen.setVisible(true);

		
	}
}
