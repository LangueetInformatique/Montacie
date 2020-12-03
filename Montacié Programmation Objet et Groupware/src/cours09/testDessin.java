package cours09;

import javax.swing.*;

import java.awt.*;

/**
 * @author montacie
 */
public class testDessin  {
    public static void main(String[] args) {
        JFrame fen = new JFrame("Gestion des dessins");
        fen.setSize(280, 280); 
		JPanel p = new JPanel();
		fen.getContentPane().add(p);  
		
		p.setLayout(new GridLayout(1,1));
        Dessin d = new Dessin(); p.add(d);
        fen.setVisible(true);
    }
}
