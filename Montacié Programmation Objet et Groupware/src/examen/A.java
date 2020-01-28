package examen;

public class A {
	String t;

	public A(String v1) { t = v1; System.out.println("A " + t); }

	private boolean m(String v1) {
		int v2 = v1.compareTo(t);
		System.out.println("A " + v1 + " " + v2);
		return (v2 == 0);
	}

	protected boolean m(String v1, boolean v2) {
		boolean v3 = m(v1);
		System.out.println("A " + v1 + " " + v2 + " " + v3);
		return (v2 == v3);
	}
}
