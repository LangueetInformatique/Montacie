/*
 * Cr�� le 14 mai 2006
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours09;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class Connexion {

	Connection con = null;
	
	public Connexion() {
		Chargement();
		try {
			String url = "jdbc:mysql://192.168.1.102:3306/Ilgii1";
			Properties props = new Properties();
			props.setProperty("user","ilgii1");
	    	props.setProperty("password","milgii1");
			con = DriverManager.getConnection(url, props);
			System.out.println("Connexion � la base donn�es");			
		} catch (SQLException ex) {
			System.out.println("Erreur de connexion � la base donn�es");
		}
		
	}
	
	private void Chargement() {
		try {
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			System.out.println("Chargement du pilote");
		} catch (Exception ex) {
			System.out.println("Erreur de chargement du pilote");
		}
	}
	
	public Connection getConnexion() {
			return con;
}
	
	public void close() {
		try {
		con.close();
		System.out.println("Fermeture de connexion � la base donn�es");
		}
		catch (SQLException ex) {
			System.out.println("Erreur de fermeture de connexion � la base donn�es");
		}
		}

}
