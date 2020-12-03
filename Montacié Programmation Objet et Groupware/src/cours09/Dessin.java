
package cours09;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

public class Dessin extends JPanel {
	private static final long serialVersionUID = 178;
	
	 public void paintComponent(Graphics g) {

		 // lecture de la taille du paneau
		 int height  = this.getHeight();
		 int width = this.getWidth();

		 // effacement du dessin precedent
		 g.clearRect(0, 0, width, height);

		 // nouveau dessin
		 g.drawOval(0, 0, width, height);
		 g.setColor(Color.ORANGE);
		 g.fillRect(width/4, height/4, width/2, height/2);
		 g.setColor(Color.BLUE);
		 g.drawString("rectangle orange dans un ovale", width/4, height/2);
	 }

}
	 
