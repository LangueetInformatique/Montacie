package atelier12;

import java.awt.Color;

import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.DefaultStyledDocument;

public class testStyle {


	public static void main(String[] args) {
		
		// Définition du style stl
		
		DefaultStyledDocument dsd = new DefaultStyledDocument();
		Style stl = dsd.addStyle("stl" , null);
		StyleConstants.setForeground(stl, Color.BLUE);
		StyleConstants.setFontSize(stl, 22);
		StyleConstants.setItalic(stl, true);
		StyleConstants.setFontFamily(stl, "Times New Roman");

	}

}
