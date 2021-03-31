/*
 * Cr�� le 13 mai 2006
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours09;

import java.sql.*;

public class testConsultation {

	public static void main(String[] args) {
		Connexion c = new Connexion();
		Connection con = c.getConnexion();
		Statement req = null;
		try {
			req = con.createStatement();
			ResultSet res = req.executeQuery("SELECT Nom, Age FROM personne ;");
			while (res.next()) {  
				String nom = res.getString("Nom");
				byte age = res.getByte("Age");
				System.out.println("L'age de "+nom+" est : " + age); }
			req.close(); 
		} catch (SQLException e) {
			System.out.println("Erreur requete");
		}
		c.close();

	}
}