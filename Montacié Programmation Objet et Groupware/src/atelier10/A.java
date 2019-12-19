package atelier10;

public class A extends B {
	static String a_initialiser = "montacié"; //

	A(char b, char c, int m) {
		super(b, c, m);
		for (int i = 0; i < n; i++)
			a_initialiser += d[i];
	}

	public void m1(int m) {
		for (int i = 0; i < n; i++) {
			System.out.println(d[i]);
		}
	}

	public static void main(String[] args) {
		A b = new A('h', a_initialiser.charAt(2), 7);
		b.m1(5);
		b.m2(3);
	}
}