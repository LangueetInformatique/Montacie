package cours03;

public class BranchementConditionnel {

	public static void main(String[] args) {

		// exemple 1
		int x = -21, valAbsolue = x;
		if (x < 0)
			valAbsolue = -x;
		System.out.println("valeur absolue de " + x + " : " + valAbsolue);

		// exemple 2
		char c = 's';
		if (c == 'S' || c == 's') {
			System.out.println("Stop, j'arr�te : je sors du programme!");
			System.exit(0);
		} else {
			System.out.println("Je continue en s�quence...");
			System.out.println("tranquillement.");
		}
	}

}

