package atelier11;

import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

public class MaPremiereFenetre {

	public static void main(String[] args) {

		// Declaration de la JFrame
		JFrame fen = new JFrame("Montacié");
		fen.setSize(280, 280);
		JPanel p = new JPanel();
		p.setBackground(Color.magenta);
		fen.getContentPane().add(p);
		
		JMenuBar mb = new JMenuBar();
		p.add(mb);
		JMenu m = new JMenu("prenoms");
		mb.add(m);
		// composants du menu
		m.add("Claude1"); m.add("Claude2");
		
		
		// Affichage de la JFrame et de son contenu
		fen.setVisible(true);

	}

}
