package atelier12;

import java.awt.Color;
import java.awt.Container;
import java.io.IOException;

import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.DefaultStyledDocument;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;

public class testStyle {

	public static void main(String[] args) {

		// Définition du style stl

		DefaultStyledDocument dsd = new DefaultStyledDocument();
		Style st1 = dsd.addStyle("st1", null);
		StyleConstants.setForeground(st1, Color.BLUE);
		StyleConstants.setFontSize(st1, 22);
		StyleConstants.setItalic(st1, true);
		StyleConstants.setFontFamily(st1, "Times New Roman");

		// insertion d'un texte dans un document
		try {
			dsd.insertString(0,
					"Après plus de six semaines de course, le skippeur Yannick Bestaven s’est installé en tête du Vendée Globe, mercredi 16 décembre, alors qu’il navigue aux portes de l’océan Pacifique, qui sera pour lui une découverte.",
					null);
		} catch (BadLocationException e) {
		}

		// utilisation du style st1
		modifStyle(dsd, st1, 0, 10);

		// association du document à une JTextPane
		JTextPane tp = new JTextPane(dsd);

//		affichage
		JFrame fen = new JFrame("testStyle");
		fen.setSize(400, 500);
		Container jp = fen.getContentPane();
		jp.add(tp);
		fen.setVisible(true);

	}

	public static void modifStyle(DefaultStyledDocument dsd, Style s, int debut, int taille) {
		dsd.setCharacterAttributes(debut, taille, s, true);

	}

}
