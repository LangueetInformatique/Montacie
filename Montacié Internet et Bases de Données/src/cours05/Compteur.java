package cours05;

import javax.swing.*;

public class Compteur extends Thread {
	JTextPane tp;
	int delai;

	// constructeur
	Compteur(int d) {
		delai = d;
		tp = new JTextPane();
		JFrame fen = new JFrame();
		fen.setSize(100, 100);
		fen.getContentPane().add(tp);
		fen.setVisible(true);
	}

	// methode appelee a l'execution du thread
	public void run() {
		int i = 0;
		while (true) {
			tp.setText(Integer.toString(i));
			i++;
			try {
				sleep(delai);
			} catch (InterruptedException e) {
			}
		}
	}
}
