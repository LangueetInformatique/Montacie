package atelier10;

public abstract class B {
	char d[];
	static int n;

	B(char b, char c, int m) {
		n = m;
		d = new char[n];
		for (int i = 0; i < n; i++) {
			if ((i % 3) == 0)
				d[i] = b;
			else
				d[i] = c;
		}
	}

	abstract public void m1(int m);

	public void m2(int m) {
		for (int i = 0; i < n; i += m) {
			System.out.println(d[i]);
		}
	}
}
