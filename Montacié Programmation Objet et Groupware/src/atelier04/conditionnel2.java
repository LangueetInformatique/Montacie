package atelier04;

public class conditionnel2 {

	public static void main(String[] args) {
		int p1 = 10, p2 = -1, p3 = 9, p4 = 4, p5 = 8;

		minimum(p1, p2, p3);
		minimum(p1, p3, p2);
		minimum(p2, p1, p3);
		minimum(p2, p3, p1);
		minimum(p3, p1, p2);
		minimum(p3, p2, p1);
	}

	public static int minimum(int p1, int p2, int p3) {
		int p4;

		if (p1 > p2) {
			if (p2 > p3)
				p4 = p3;
			else
				p4 = p2;
		} else {
			if (p1 > p3)
				p4 = p3;
			else
				p4 = p1;
		}

		System.out.print(p4);

		return p4;
	}
}
