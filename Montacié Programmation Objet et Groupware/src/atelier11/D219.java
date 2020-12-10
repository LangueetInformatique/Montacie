package atelier11;

import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;

public class D219 {

	public static void main(String[] args) {

		// Declaration de la JFrame
		JFrame fen = new JFrame("D219");
		fen.setSize(1000, 1000);
		JPanel p = new JPanel();
		fen.getContentPane().add(p);
		p.setLayout(new GridLayout(5,4));
		
		String nom = "Montacié";
		String[] prenoms = {"Claude1","Claude2"};
		Color c = Color.magenta;
		
		PanneauPrenom pp1 = new PanneauPrenom(c, nom, prenoms);
		p.add(pp1);
		
		nom = "Eyharabide";
		String[] prenoms2 = {"Victoria1","Victoria2"};
		c = Color.blue;
		PanneauPrenom pp2 = new PanneauPrenom(c, nom, prenoms2);
		p.add(pp2);
		
		
		
		// Affichage de la JFrame et de son contenu
		fen.setVisible(true);

	}

}
