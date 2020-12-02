package cours08;

import javax.swing.*;
import java.awt.*;

/**
 * @author montacie
 */
public class testJTable {

	public static void main(String[] args) {
		// noms des champs
		String[] nomChamps = {"Nom", "Marque","Cylindr�e"};

		// valeurs des champs
		Object[][] garage = {
			{"Twingo", "Renault", "1239"},
			{"Marbella", "Seat","903"},
			{"Corsa", "Opel","1686"},
			};
		
		// affichage de la table
		JTable tb = new JTable(garage, nomChamps);
		// ajout d'un ascenseur
		new JScrollPane (tb);

		JFrame fen = new JFrame("Affichage d'une table"); fen.setSize(500, 100);
		Container cpfen = fen.getContentPane(); 
		cpfen.add(tb);
		fen.setVisible(true);
	}
}
