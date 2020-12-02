package cours08;

import javax.swing.*;
import java.awt.*;

public class testMenu {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
//		 D�claration du conteneur racine 
		JFrame fen = new JFrame("Exemples de menus d�roulants"); fen.setSize(500, 120);
		JPanel p = new JPanel();
		fen.getContentPane().add(p);  
		p.setLayout(new GridLayout(4,2));

//		 D�claration de la barre de menu
		JMenuBar mb = new JMenuBar ();


//		 D�claration des diff�rents menus
		JMenu m1 = new JMenu("menu 1"); 
		JMenu m2 = new JMenu("menu 2");
		JMenu m3 = new JMenu("menu 3 de cases � cocher"); 
		JMenu m4 = new JMenu("menu 4 de boutons radio");
		
//		 composants du menu 1
		m1.add("bleu"); m1.add("rouge"); m1.add("vert");

//		 composants du menu 2

//		 composants du sous-menu 1 du menu 2
		JMenu m21 = new JMenu("menu 2.1"); m21.add("homme"); m21.add("femme"); m2.add(m21);

		JMenuItem mi = new JMenuItem("menu 2.2"); 
		m2.add(mi);

//		 composants du menu 3
		JCheckBoxMenuItem cbmi1 = new JCheckBoxMenuItem("petit"); m3.add(cbmi1);
		JCheckBoxMenuItem cbmi2 = new JCheckBoxMenuItem("grand"); m3.add(cbmi2);

		//		 composants du menu 4
		JRadioButtonMenuItem rbmi1, rbmi2;
		rbmi1 = new JRadioButtonMenuItem("piquant"); m4.add(rbmi1); rbmi2 = new JRadioButtonMenuItem("doux"); m4.add(rbmi2);      

//		 ajout des menus � la barre de menu
		mb.add(m1); mb.add(m2); mb.add(m3); mb.add(m4); 

//		 ajout de la barre de menu au conteneur
		p.add(mb); 
		fen.setVisible(true);

	}

}
