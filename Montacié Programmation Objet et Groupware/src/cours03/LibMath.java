package cours03;
/**
 * Librairie math�matique. Des fonctions usuelles�
 */
public class LibMath {
	/**
 	 * Minimum de deux r�els
 	 * @param x : premier argument r�el
 	 * @param y : deuxi�me argument r�el
 	 * @return : le minimum de x et y
 	*/
	static double mini(double x, double y){
		double leMin;
		if (x<y) leMin=x;
		else leMin=y;
		return (leMin);
	}
}
