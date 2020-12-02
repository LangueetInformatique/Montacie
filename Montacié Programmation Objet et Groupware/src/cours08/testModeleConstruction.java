package cours08;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;

/**
 * @author montacie
 */
public class testModeleConstruction {

	public static void main(String[] args) {
//		D�claration de la JFrame
	 JFrame fen = new JFrame("Construction des objets Swing"); fen.setSize(280, 280); 
	 JPanel p = new JPanel();
	 fen.getContentPane().add(p);  
	 p.setLayout(new GridLayout(2,2));
//		D�claration du JMenuBar
	 JMenuBar mb = new JMenuBar();
		 // D�claration du JMenu
		 JMenu m = new JMenu("Choix des composants"); 
		 m.add("champ"); m.add("bouton"); m.add("menu"); mb.add(m);
	 p.add(mb);  
//		D�claration du JButton
	 JButton b1 = new JButton("Lancer"); p.add(b1); 
//		D�claration du 1er JPanel
	 JPanel p1 = new JPanel(); p1.setBackground(Color.BLUE);         
	 p1.setToolTipText("Etiquette sensitive"); p.add(p1);  
//		D�claration du 2�me JPanel
	 JPanel p2 = new JPanel(); p2.setBackground(Color.ORANGE);        
	 p2.setBorder(new TitledBorder("Panneau 2")); p.add(p2); 

//		Affichage de la JFrame et de son contenu
	 fen.setVisible(true);

	}
}
