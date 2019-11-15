package cours06; 
import java.io.*; 
import java.util.*;
import util.Keyboard;

public class testLctTxtFmt {
	public static void main(String[] args) {
		String ligne;	
		try {
			File f = new File(Keyboard.getString("Nom du fichier � lire : "));
			FileReader fr = new FileReader(f);
			BufferedReader br = new BufferedReader(fr);
			while ((ligne=br.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(ligne, "[;\n\t]");
				while (st.hasMoreTokens()) 
					System.out.print(st.nextToken());
				System.out.print("\n"); 
			}
			br.close();
		} 
		catch (IOException e) { e.printStackTrace(); }
	} 
}
