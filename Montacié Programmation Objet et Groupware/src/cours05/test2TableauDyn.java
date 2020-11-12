package cours05;

public class test2TableauDyn {
	public static void main(String[] args) {
		TableauDyn phrase = new TableauDyn(2,5);
		String mot;
		phrase.puts(0, "le");
		mot = phrase.get(0); System.out.println(mot);
		phrase.puts(1, "livre");
		mot = phrase.get(1); System.out.println(mot);
		phrase.puts(2, "de");
		mot = phrase.get(2); System.out.println(mot);
		mot = phrase.get(10); System.out.println(mot);
	}
}

