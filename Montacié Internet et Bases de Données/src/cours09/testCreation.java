package cours09;

import java.sql.*;

public class testCreation {



	public static void main(String[] args) {
		Connexion c = new Connexion();
		Connection con = c.getConnexion();
		try {
			Statement req = con.createStatement();
			//     cr�ation d�une table de donn�es
			String tb1 = "personne (Nom CHAR (20), Masculin BIT, Age TINYINT);";
			req.execute("create table " + tb1);
			System.out.println("Cr�ation de la table " + tb1);
			String tb2 = "vente (Montant NUMERIC, date DATE);";
			req.execute("create table " + tb2);
			System.out.println("Cr�ation de la table " + tb2);
			// 		destruction de la table
			req.execute("drop table vente");
			System.out.println("Destruction de la table " + tb2);
			req.close();
		} catch (Exception e) {
			System.out.println("Erreur requete");
		}
		c.close();

	}
}