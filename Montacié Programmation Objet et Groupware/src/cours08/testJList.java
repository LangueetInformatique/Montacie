/*
 * Cr�� le 7 d�c. 2005
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours08;

import java.awt.Container;

import javax.swing.*;

public class testJList {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		// valeurs des �l�ments de la liste
		Object[] tagSyntaxe = { "abr�viation", "adjectif", "adverbe", "article", 
			"conjunction", "nom", "numeral", "pronom", "pr�position" };
		JList list = new JList(tagSyntaxe);
		
		// affichage de la liste
		JFrame fen = new JFrame("Affichage d'une liste"); fen.setSize(500, 500);
		Container cpfen = fen.getContentPane(); 
		cpfen.add(list);
		fen.setVisible(true);
		
		// s�lection de valeurs dans la liste
		Object[] select = list.getSelectedValues();
		for (int i = 0;i < select.length;i++)
			System.out.println(select[i]);
		

	}

}
