package atelier04;

public class conditionnel3 {

	public static void main(String[] args) {

		int p1 = 10, p2 = -1, p3 = 9, p4 = 4, p5 = 8;

		mediane(p1, p2, p3);
		mediane(p1, p3, p2);
		mediane(p2, p1, p3);
		mediane(p2, p3, p1);
		mediane(p3, p1, p2);
		mediane(p3, p2, p1);
	}

	public static int mediane(int p1, int p2, int p3) {
		int p4;

		if (p1 > p2) {
			if (p3 > p1)
				p4 = p1;
			else {
				if (p3 > p2)
					p4 = p3;
				else
					p4 = p2;
			}
		} else {
			if (p3 > p2)
				p4 = p2;
			else {
				if (p3 > p1)
					p4 = p3;
				else
					p4 = p1;
			}
		}

		System.out.print(p4);

		return p4;
	}

}
