/*
 * Cr�� le 13 mai 2006
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours09;

import java.sql.*;

public class testUpdate {

	public static void main(String[] args) {
		Connexion c = new Connexion();
		Connection con = c.getConnexion();
		PreparedStatement preq = null;
		String[] nom = {"Chirac", "Villepin", "Sarkozy", "Alliot-Marie"};
		boolean[] masculin = {true, true, true, false};
		byte[] age = {70, 65, 55, 50};
		try {
			preq = con.prepareStatement("insert into personne values (?, ?, ?)");
			for (int i = 0;i < nom.length;i++) {
				preq.setString(1, nom[i]);
				preq.setBoolean(2, masculin[i]);
				preq.setByte(3, age[i]);
				//		     envoi des requetes
				preq.executeUpdate();
			}
			preq.close();
			con.close();
		} catch (Exception e) {
			System.out.println("Erreur requete");
		}

	}
}