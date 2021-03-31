package cours06;

public class testLectureMessage {

	public static void main(String args[]) {
		LectureMessage p = new LectureMessage("pop.laposte.net", 110);
		System.out.println(p.nbMessages("ilgii1", "milgii1"));
		p.fin();
	}

}
