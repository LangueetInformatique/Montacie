package atelier11;

import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;

public class testPanneauPrenom {

	public static void main(String[] args) {
		
		String nom = "Montacié";
		String[] prenoms = {"Claude1","Claude2"};
		Color c = Color.magenta;

		// Declaration de la JFrame
		JFrame fen = new JFrame(nom);
		fen.setSize(280, 280);
		PanneauPrenom pp = new PanneauPrenom(c, nom, prenoms);
		fen.getContentPane().add(pp);
		
		// Affichage de la JFrame et de son contenu
		fen.setVisible(true);
		

	}

}
