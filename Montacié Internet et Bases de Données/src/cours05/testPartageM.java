
package cours05;

public class testPartageM {
	public static void main(String args[]) { // creation et activation des 5
												// Processus
		for (int i = 0; i < 5; i++) {
			Thread p = new ProcessusPartageM();
			p.start();
		}
	}
}
