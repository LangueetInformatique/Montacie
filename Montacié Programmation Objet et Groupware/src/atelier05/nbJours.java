package atelier05;

import cours04.Date;

public class nbJours {

	public static void main(String[] args) {
		Date fete = new Date(14, 7, 2021);
		Date aujourdhui = new Date(22, 10, 2020);

		int nb = 0;

		while (aujourdhui.CompareTo(fete) == true) {
			aujourdhui.Incrementer();
			nb++;
		}

		System.out.println(nb);

	}

}
