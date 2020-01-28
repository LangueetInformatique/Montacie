package examen;

public class B implements I {
	boolean b;
	A a;

	public B(boolean v1, boolean v2, A v3) { b = v1 & v2; a = v3; }

	double m(double v1, double v2) {
		double v3;
		if (b == true)
			v3 = v1 - v2;
		else
			v3 = v1 + v2;
		System.out.println("B " + v1 + " " + v2 + " " + v3);
		a.m("juin", true);
		return v3;
	}
	
	public static void main(String[] args) {
		B b = new B(true, false, new A(a_initialiser));
		b.m(8.2, 5.1);
	}
}
