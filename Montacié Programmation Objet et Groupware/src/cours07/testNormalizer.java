package cours07;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;


import com.ibm.icu.text.Normalizer;

public class testNormalizer {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		String s = null;
		StringBuffer s1;
		try {
			File fin = new File("src/cours07/caract�res.txt");
			BufferedReader br = new BufferedReader(new FileReader(fin));
			s = br.readLine();
			br.close();
			
			File fout = new File("src/cours07/caract�resN.txt");
			PrintWriter pw = new PrintWriter(fout);
			
			System.out.println(s.length());
			
			pw.print(s);
			s1 = new StringBuffer(Normalizer.normalize(s, Normalizer.NFD));
			char c = s1.charAt(8); 
			s1.setCharAt(5, c);
			s1.deleteCharAt(8);
			
			pw.print(Normalizer.compose(new String(s1), true));
			
			pw.close();
		
		} 
		catch (IOException e) { e.printStackTrace(); }
		
		
		

	}

}
