package cours06;  
import java.io.*;
import util.Keyboard;
public class tstLctTxt {
	public static void main(String[] args) {
		String ligne;
		try {
			File f = new File(Keyboard.getString("Nom du fichier � lire : "));
			FileReader fr = new FileReader(f);
			BufferedReader br = new BufferedReader(fr);
			while ((ligne=br.readLine()) != null) {
				System.out.println(ligne); 
			}
			br.close();
		} 
		catch (IOException e) { e.printStackTrace(); }
	} 
}
