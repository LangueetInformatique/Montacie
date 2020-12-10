package atelier11;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;

import java.awt.Color;

public class PanneauPrenom extends JPanel {
	
	public PanneauPrenom(Color c, String nom, String[] prenoms) {
		this.setBackground(c);
		JMenuBar mb = new JMenuBar();
		this.add(mb);
		JMenu m = new JMenu("prenoms");
		mb.add(m);
		for (int i = 0;i < prenoms.length;i++)
			m.add(prenoms[i]);	
	}

}
