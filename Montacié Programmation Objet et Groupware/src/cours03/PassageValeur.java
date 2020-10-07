package cours03;
public class PassageValeur {
	static void f(int x){
		int y=10;
		x*=y;
		System.out.println("x="+x);
	}
	public static void main(String[] args) {
		int valeur=1;
		f(valeur);
		System.out.println("valeur="+valeur);
	}
}
