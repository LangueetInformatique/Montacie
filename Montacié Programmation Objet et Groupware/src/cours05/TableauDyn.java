package cours05;

public class TableauDyn extends Tableau {    
	protected int pas_=0;
 /** cr�ation d'une nouvelle instance de TableauDyn
  * @param t taille du tableau originel
  * @param pas, pas d'augmentation de taille du tableau
  */
 	public TableauDyn(int t, int pas) { super(t); pas_ += pas; }
	/** �criture d'un �l�ment dans le tableau
 	 * @param i indice du tableau
 	 * @param mot �l�ment � �crire
	 */
	public void puts(int i, String mot) {
 		try { super.put(i, mot); }
   catch (IndexOutOfBoundsException e) {
   	System.out.println("Elargissement du tableau � une taille de "+(tab_.length+pas_));
   	String[] newtab = new String[tab_.length + pas_];
    	for (int j = 0;j < tab_.length;j++) newtab[j] = tab_[j];
   	tab_ = newtab; puts(i, mot);
		}}}

