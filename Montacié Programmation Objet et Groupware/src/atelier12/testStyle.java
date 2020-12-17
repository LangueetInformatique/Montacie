package atelier12;

import java.awt.Color;
import java.io.IOException;

import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.DefaultStyledDocument;
import javax.swing.text.BadLocationException;

public class testStyle {

	public static void main(String[] args) {

		// Définition du style stl

		DefaultStyledDocument dsd = new DefaultStyledDocument();
		Style stl = dsd.addStyle("stl", null);
		StyleConstants.setForeground(stl, Color.BLUE);
		StyleConstants.setFontSize(stl, 22);
		StyleConstants.setItalic(stl, true);
		StyleConstants.setFontFamily(stl, "Times New Roman");

		try {
			dsd.insertString(0,
					"Après plus de six semaines de course, le skippeur Yannick Bestaven s’est installé en tête du Vendée Globe, mercredi 16 décembre, alors qu’il navigue aux portes de l’océan Pacifique, qui sera pour lui une découverte.",
					null);
			System.out.println(dsd.getText(0, dsd.getLength()));
		} catch (BadLocationException e) {
		}

	}

}
