
package cours09;

import javax.swing.*;
import java.awt.event.*;
import java.awt.Graphics;

public class PanneauDessinSouris extends JPanel implements MouseMotionListener {
	private static final long serialVersionUID = 180;

	private int X, Y;

//	 ajout d'un ecouteur sur le panneau    
	public PanneauDessinSouris() {
		addMouseMotionListener(this);
	}

//	 traitement de tous les evenements du panneau de type Mouse Motion 
	public void mouseMoved(MouseEvent e) {
		X = e.getX();
		Y = e.getY();
		repaint();
	}

	public void mouseDragged(MouseEvent e) {
	}

	public void paintComponent(Graphics g) {
		g.drawLine(0, 0, X, Y);
	}
}
