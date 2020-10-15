package atelier04;

public class conditionnel1 {

	public static void main(String[] args) {

		int p1 = 10, p2 = 9, p3 = -1, p4 = 4, p5 = 8;
		
		if (p1 > p2) {
			if (p1 > p3)
				p4 = p1;
			else p4 = p3;
		}
		else {
			if (p2 > p3)
				p4 = p2;
			else p4 = p1;
		}
		
		System.out.println(p4);

	}

}
