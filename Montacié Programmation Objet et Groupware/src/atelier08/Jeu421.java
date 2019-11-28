package atelier08;

public class Jeu421 {

	public static void main(String[] args) {
		Aleat d1, d2, d3;
		d1 = new Aleat(6);
		d2 = new Aleat(6);
		d3 = new Aleat(6);
		lancerDes(d1, d2, d3);

	}
	
	public static TroisDes lancerDes(Aleat d1, Aleat d2, Aleat d3) {
		return (new TroisDes(d1.get(), d2.get(), d3.get()));
	}

}
