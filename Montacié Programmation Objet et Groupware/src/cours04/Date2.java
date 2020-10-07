package cours04;

import java.util.Calendar;

/** Cr�ation et gestion am�lior�es de dates 
 * (seconde, minute, heure, jour, mois, ann�e) 
 */
public class Date2 extends Date {
private int seconde, minute, heure;

public Date2(int j, int m, int a) {
	super(j, m, a);// appel du constructeur de Date
	heure = Calendar.HOUR_OF_DAY;
	minute = Calendar.MINUTE;
	seconde = Calendar.SECOND;
	}

public Date2() {
	super(0, 0, 0); 	// sinon appel automatique du constructeur vide de Date
	heure = Calendar.HOUR_OF_DAY;
	minute = Calendar.MINUTE;
	seconde = Calendar.SECOND;
	}

/** Red�finition - Affichage de la date et de l'heure */
public void Afficher() {
	super.Afficher();
	System.out.println(heure+" "+minute+" "+seconde); 
}

/** Affichage de l'heure */
public void Afficher2() {
	System.out.println(heure+":"+minute+":"+seconde); 
	}

} // fin de la d�finition de la classe Date2

