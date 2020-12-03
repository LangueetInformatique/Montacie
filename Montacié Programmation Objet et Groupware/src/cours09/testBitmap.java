
package cours09;

import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class testBitmap {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
	       JFrame fen = new JFrame("Gestion des bitmaps");
	        fen.setSize(280, 280); 
			JPanel p = new JPanel();
			fen.getContentPane().add(p);  
			
			p.setLayout(new GridLayout(1,1));
	        Bitmap b = new Bitmap("src/cours09/Sorbonne.jpg"); p.add(b);
	        fen.setVisible(true);

	}

}
