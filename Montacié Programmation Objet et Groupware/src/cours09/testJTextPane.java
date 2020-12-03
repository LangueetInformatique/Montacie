package cours09;

import java.awt.*;
import javax.swing.*;
import javax.swing.text.*; 
import java.io.*;
import com.ibm.icu.text.BreakIterator;


/**
 * @author montacie
 */
public class testJTextPane {

	public static void main(String[] args) {
		String NomFichier = "livres/avare.txt";
		JTextPane tp = new JTextPane();
        
        // lecture du document
		try { 
			tp.read(new FileReader(NomFichier), null); }
		catch (IOException e) {}

		// definition du style Personnage
		StyledDocument dsdoc = tp.getStyledDocument();
		dsdoc.putProperty("Titre" , "L'avare");
		Style s = dsdoc.addStyle("Personnage" , null);
		StyleConstants.setForeground(s, Color.PINK);
		StyleConstants.setFontSize(s, 16);
		StyleConstants.setBold(s, true);
		
		//	enrichissement du texte
		
		String cc = null;
		try {cc = dsdoc.getText(0, dsdoc.getLength()); }
		catch (BadLocationException e) {}
		
		BreakIterator bi1 = BreakIterator.getWordInstance();
		bi1.setText(cc);
		int debut = bi1.first();
		for (int fin = bi1.next(); fin != BreakIterator.DONE; debut = fin, fin = bi1.next()) {
			if  (cc.substring(debut, fin).matches("[A-Z]*"))
			dsdoc.setCharacterAttributes(debut, fin-debut, s, true);
		}
		
		//	affichage
		JFrame fen = new JFrame ("L'avare");
		fen.setSize(400, 500);
		Container jp = fen.getContentPane();
		jp.add(tp);
		jp.add(new JScrollPane(tp));
		fen.setVisible(true);

	}
}
