package cours08;

import javax.swing.*;
import java.awt.*;

/**
 * @author montacie
 */
public class testJColorChooser {

	public static void main(String[] args) {
		
		Color initialColor = Color.red;
		
		JFrame fen = new JFrame();
   		Color newColor = JColorChooser.showDialog(fen, "Recherche d'une couleur", initialColor);
   		System.out.println(newColor.toString());

	}
}
