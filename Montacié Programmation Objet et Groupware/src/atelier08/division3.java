package atelier08;

public class division3 {

	public static void main(String[] args) {
		try {
			division();
		} catch (ArithmeticException e) {
			System.out.print("j'ai capture l'exception avec le message ");
			System.out.println(e.getMessage());
		}

	}

	public static void division() throws ArithmeticException {
		int i = 1000, j;
		do {
			i--;
			j = 1 / i;
		} while (i >= 0);
		System.out.println("fin du programme");
	}

}
