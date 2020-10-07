package cours03;

public class ChoixMultiple {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		char c='o';
		switch (c) {
			case 'o':
			case 'O':	System.out.println("oui");
				break;
			case 'n':
			case 'N':	System.out.println("non");
				break;
			default :System.out.println("peut-�tre");
		}


	}

}
