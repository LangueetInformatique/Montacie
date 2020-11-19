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
		} catch (ArithmeticException e) {
			System.out.print("j'ai capture l'exception avec le message ");
			System.out.println(e.getMessage());

		}
	}

}
