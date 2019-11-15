package cours06;

import java.io.*;
import cours04.Date;


public class Date3 extends Date implements Serializable {
	private static final long serialVersionUID = 176;
	
	public Date3(int j, int m, int a) {super(j,m,a);}
	public Date3() {super(0,0,0);}
	
	public void Sauvegarder(File f, boolean ajout) {
		try {
		FileOutputStream fos = new FileOutputStream(f, ajout);
		ObjectOutputStream oos = new ObjectOutputStream(fos);
		oos.writeObject(this); 
		oos.close();
	}
	catch (IOException e) { e.printStackTrace(); }
	}

}
