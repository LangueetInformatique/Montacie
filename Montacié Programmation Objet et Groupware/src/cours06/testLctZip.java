package cours06; import java.io.*; import java.util.zip.*;
import util.Keyboard;
public class testLctZip {
	public static void main(String[] args) {
		String d;
		try {
			File f = new File(Keyboard.getString("Nom du fichier compress� : "));
			FileInputStream fis = new FileInputStream(f);
			InflaterInputStream is = new InflaterInputStream(fis);
			DataInputStream idis = new DataInputStream(is);
			while ((d=idis.readUTF()) != null){
				System.out.println(d);
			}
			idis.close();
		}
		catch (EOFException e) { System.out.println("Fin de lecture de fichier"); }
		catch (IOException e) { e.printStackTrace(); }
	}
}
