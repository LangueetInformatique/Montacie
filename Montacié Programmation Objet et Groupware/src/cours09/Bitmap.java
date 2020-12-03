
package cours09;


import java.awt.*;
import javax.swing.*;


public class Bitmap extends JPanel {
	private static final long serialVersionUID = 177;
	
	Image im;
	
	public Bitmap(String nomImage) {
		im = getToolkit().getImage(nomImage);
	}
	
	 public void paintComponent(Graphics g) {

		 // lecture de la taille du paneau
		 int height  = this.getHeight();
		 int width = this.getWidth();
		 
		 // effacement du dessin precedent
		 g.clearRect(0, 0, width, height);
		
		 //	affichage de l'image
		 g.drawImage(im, 0, 0, this);

	
	 }

}