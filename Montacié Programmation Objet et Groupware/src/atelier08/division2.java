package atelier08;

public class division2 {

	public static void main(String[] args) {
		try {
			int i = 1000, j;
			do {
				i--;
				j = 1 / i;
			} while (i >= 0);
			System.out.println("fin du programme");
		} catch (ArithmeticException o) {
			System.out.println("j'ai capturé l'exception");

		}
	}

}
