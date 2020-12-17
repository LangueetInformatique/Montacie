package atelier12;

import java.awt.GridLayout;
import java.io.FileReader;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextPane;

public class MultiFenetre {

	private JFrame frame;
	private JTextPane[] fen;
	private JPanel pan;

	public MultiFenetre(int nFen) {
		frame = new JFrame("MultiFenetre");
		frame.setSize(nFen * 200, 500);
		pan = new JPanel();
		pan.setLayout(new GridLayout(2, nFen));
		fen = new JTextPane[nFen];
		for (int i = 0; i < nFen; i++) {
			fen[i] = new JTextPane();
			pan.add(fen[i]);
		}
		frame.getContentPane().add(pan);
	}

	public void afficherdoc(String nomFichier, int iFen) {
		// lecture du document
		try {
			fen[iFen].read(new FileReader(nomFichier), null);
		} catch (IOException e) {
		}
		frame.setVisible(true);
	}

	public void affichertxt(String texte, int iFen) {
		fen[iFen].setText(texte);
		frame.setVisible(true);
	}

}
