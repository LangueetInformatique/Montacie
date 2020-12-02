package cours08;

import javax.swing.*;
import java.io.*;

/**
 * @author montacie
 */
public class testJFileChooser {

	public static void main(String[] args) {
		JFileChooser fc = new JFileChooser("/");
		JFrame fen = new JFrame();
		fc.showOpenDialog(fen);
		File selFile = fc.getSelectedFile();
		System.out.println(selFile.getName());
	}
}
