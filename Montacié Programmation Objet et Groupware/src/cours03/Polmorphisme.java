package cours03;

public class Polmorphisme {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		affiche(18); affiche(6.57); affiche(4,1);
	}
	
	static void affiche(int x) {
		System.out.println("Entier : "+x);
	}
	static void affiche(double x) {
		System.out.println("R�el : "+x);
	}
	static void affiche(int x1, int x2) {
		 System.out.println("Couple : ("+x1+","+x2+")");
	}


}
