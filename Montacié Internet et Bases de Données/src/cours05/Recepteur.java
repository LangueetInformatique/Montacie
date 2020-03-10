
package cours05;

import java.io.*;

import javax.swing.*;

public class Recepteur extends Thread {
	JTextPane tp;
	BufferedReader br;

	public Recepteur(PipedReader in) {
		br = new BufferedReader(in);
		tp = new JTextPane();
		JFrame fen = new JFrame();
		fen.setSize(100, 100);
		fen.getContentPane().add(tp);
		fen.setVisible(true);
	}

	public void run() {
		String mess = null;
		while (true) {
			try {
				mess = br.readLine();
			} catch (IOException e) {
			}
			tp.setText(mess);
		}

	}

}
