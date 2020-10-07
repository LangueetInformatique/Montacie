/*
 * Créé le 30 oct. 2011
 *
 */
package cours04;

/** création et gestion d'une figure géométrique
*/
public abstract class FigureGeometrique {
    protected String couleur = "noir";

    /** création d'une nouvelle instance de la classe FigureGeometrique
     * @param co couleur de la figure
     */    
    public FigureGeometrique (String co) {
        couleur = co; // couleur par défaut
    }

	/** calcul du périmètre d'une figure géométrique
		 * @return périmètre
		 */    
		public abstract float perimetre();

		/** calcul de la surface d'une figure géométrique
		 * @return surface
		 */    
		public abstract float surface();
} // fin de définition de la classe