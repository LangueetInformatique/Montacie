package cours05;

class ProcessusPartageM extends Thread {
	static private int numero = 0;
	int numeroProcessus;

	// Contructeur
	ProcessusPartageM() {
		super(("Processus numero " + numero++));
		numeroProcessus = numero;
	}

	// Corps de l'application
	public void run() {
		for (int i = 0; i < 10; i++)
			affiche(i);
	}

	void affiche(int i) {
		try {
			sleep(100);
		} catch (InterruptedException e) {
		}
		System.out.println(this.getName() + " � l'it�ration " + i);
	}
}
