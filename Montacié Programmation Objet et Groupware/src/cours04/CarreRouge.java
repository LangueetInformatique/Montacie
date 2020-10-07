/*
 * Créé le 30 oct. 2011
 *
 */
package cours04;

/** création et gestion d'un carré rouge */
public class CarreRouge extends FigureGeometrique {

protected float cote = 0;
    
	/** Création d'une nouvelle instance de CarreRouge */
	public CarreRouge(float x) {
		super("rouge");
		cote = x;
	}
	
	/** calcul du périmètre d'un carré rouge
		* @return périmètre
	   */
		public float perimetre() { return 4*cote; }
    
		/** calcul de la surface d'un carr� rouge
		 * @return surface
		 */
		public float surface() { return cote*cote; }
    
	} // fin de définition


