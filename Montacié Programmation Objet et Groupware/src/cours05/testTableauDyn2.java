package cours05;

import util.Keyboard;

public class testTableauDyn2 {
	public static void main(String[] args) {
		TableauDyn2 phrase = new TableauDyn2(2,5);  
		phrase.puts(0, "le"); phrase.puts(1, "livre"); 
		String mot = null;
		do {     
			try {
				mot = phrase.gets(Keyboard.getInt("Indice du mot ? ")); 
   	}
   	catch (HorsBornes e){ System.out.println(e.getMessage()); }
		} while (mot == null);
		System.out.println(mot);
	}
}

