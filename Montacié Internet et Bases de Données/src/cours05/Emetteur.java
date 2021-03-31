
package cours05;

import java.io.*;
import util.*;

public class Emetteur extends Thread {
	
	PipedWriter out;
	public Emetteur(PipedWriter out) {
		this.out = out;
	}
	
	public void run() {	
		while (true) {
			String mess = Keyboard.getString("message?");
			try {
			out.write(mess + "\n");
			}
			catch (IOException e) {}
		}
	}

}
