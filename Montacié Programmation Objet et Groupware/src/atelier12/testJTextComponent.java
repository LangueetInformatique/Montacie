package atelier12;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class testJTextComponent {


	public static void main(String[] args) {
		// Declaration de la JFrame
		 JFrame fen = new JFrame("testJTextField"); fen.setSize(280, 280); 
		 JPanel p = new JPanel();
		 fen.getContentPane().add(p);
		 JTextField jtf = new JTextField("montacié");
		 p.add(jtf);
		 
		 
//			Affichage de la JFrame et de son contenu
		 fen.setVisible(true);

	}

}
