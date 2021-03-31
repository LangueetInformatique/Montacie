/*
 * Cr�� le 13 mai 2006
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours09;

import java.sql.*;

public class testMetaData {
    public static void main(String[] args) {
    	Connexion c = new Connexion();
		Connection con = c.getConnexion();
    
		try {
			DatabaseMetaData meta=con.getMetaData();
			System.out.println ("Lecture et Affichage des metadata ");
			System.out.print(" Database: "+meta.getDatabaseProductName());
			System.out.println(".Version "+meta.getDatabaseProductVersion());
			System.out.println(" User Name: "+meta.getUserName());
			ResultSet tables = meta.getTables(con.getCatalog(),null,"%",null);
//			affichage des informations
			while(tables.next()){
			   System.out.println("###################################");
			   for(int i=0; i<tables.getMetaData().getColumnCount();i++){
			      String nomColonne = tables.getMetaData().getColumnName(i+1);
			      Object valeurColonne = tables.getObject(i+1);
			      System.out.println(nomColonne+" = "+valeurColonne);
			   }

			}
    } catch (SQLException ex)
    	{System.out.println("Erreur de lecture des metadata"+ex); 
    	System.exit(0);}  

    }
}
