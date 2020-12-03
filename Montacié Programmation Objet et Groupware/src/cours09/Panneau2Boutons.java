package cours09;

import javax.swing.*;
import java.awt.event.*;

public class Panneau2Boutons extends JPanel implements ActionListener {
	private static final long serialVersionUID = 179;

	private JButton bt1, bt2;

	// creation des boutons
	public Panneau2Boutons() {
		bt1 = new JButton("clic 1");
		this.add(bt1);
		bt2 = new JButton("clic 2");
		this.add(bt2);

		// ajout des ecouteurs sur chaque bouton
		bt1.addActionListener(this);
		bt2.addActionListener(this);
	}

	// traitement de tous les evenements du panneau de type Action
	public void actionPerformed(ActionEvent ev) {
		if (ev.getSource() == bt1)
			System.out.println("clic 1");
		else
			System.out.println("clic 2");
	}
}
