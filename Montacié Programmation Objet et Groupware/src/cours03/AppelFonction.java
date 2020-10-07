package cours03;

public class AppelFonction {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		double a = 20, b = 10;
		double lePlusPetit = mini(2 * a, 5 * b);
		System.out.println("Min(" + a + ", " + b + ") : " + lePlusPetit);
		System.out.println("Minimum (2*a, 5*b) : " + mini(2 * a, 5 * b));
	}
	

	/**
	 * Minimum de deux r�els
	 * 
	 * @param x
	 *            : premier argument r�el
	 * @param y
	 *            : deuxi�me argument r�el
	 * @return : le minimum de x et y
	 */

	static double mini(double x, double y) {
		double leMin;
		if (x < y)
			leMin = x; // commentaires
		else
			leMin = y;
		return (leMin);
	}

}
