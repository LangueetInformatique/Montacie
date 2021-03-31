
package cours05;

import java.io.*;

public class testPartageF {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// creation du tube
		PipedWriter out = new PipedWriter();
		PipedReader in = null;
		try {
			in = new PipedReader(out);
			Emetteur e = new Emetteur(out);
			Recepteur r = new Recepteur(in);
			new Thread(e).start();
			new Thread(r).start();
		} catch (IOException e) {
		}
	}

}
