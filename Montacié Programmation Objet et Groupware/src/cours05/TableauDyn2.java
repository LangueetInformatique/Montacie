package cours05;

public class TableauDyn2 extends TableauDyn {
	/** cr�ation d'une nouvelle instance de TableauDyn2
 	 * @param t taille du tableau originel
 	 * @param pas, pas d'augmentation de taille du tableau
	 */
	public TableauDyn2(int t, int pas) { super(t, pas); }

	/** lecture d'un �l�ment du tableau
	 * @param i indice du tableau
	 * @return �lement
	 */    
	public String gets(int i) throws HorsBornes {
		if ((i>=0) && (i < tab_.length)) return super.get(i);
		else 
			throw new HorsBornes(i);
		}
}

