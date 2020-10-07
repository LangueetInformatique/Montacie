package cours03;
/**
 * Applicatif de test de la fonction min de LibMath�
 */
public class TestMin {

	public static void main(String[] args) {
		double a=20, b=10;
		double minimum=LibMath.mini(a,b);
		System.out.println("Minimum de " + a + " et " + b + " : " 					  + minimum);
		System.out.println("Minimum de 9 et 9 : " + LibMath.mini(9,9));
	}
}
