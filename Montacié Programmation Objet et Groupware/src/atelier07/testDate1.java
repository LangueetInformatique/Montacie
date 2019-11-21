package atelier07;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.SimpleTimeZone;
import java.util.TimeZone;

import util.Keyboard;

public class testDate1 {

	public static void main(String[] args) {
		// get the supported ids for GMT+01:00 (Heure d'Hiver en France)
		String[] ids = TimeZone.getAvailableIDs(1 * 60 * 60 * 1000);
		// if no ids were returned, something is wrong. get out.
		if (ids.length == 0)
			System.exit(0);

		// create a Heure d'Hiver en France time zone
		SimpleTimeZone pdt = new SimpleTimeZone(1 * 60 * 60 * 1000, ids[0]);
		Calendar calendar = new GregorianCalendar(pdt);
		Date trialTime = new Date();
		calendar.setTime(trialTime);
		
		int jour = calendar.get(Calendar.DAY_OF_MONTH);
		int mois = calendar.get(Calendar.MONTH) + 1;
		int annee =  calendar.get(Calendar.YEAR);
		int heure = calendar.get(Calendar.HOUR);
		int minute = calendar.get(Calendar.MINUTE);
		int seconde = calendar.get(Calendar.SECOND);
		
		System.out.print(jour+"/"+mois+"/"+annee + " ");
		System.out.println(heure+":"+minute+":"+seconde);
		
		String s = Keyboard.getString("delai");
		
		jour = calendar.get(Calendar.DAY_OF_MONTH);
		mois = calendar.get(Calendar.MONTH) + 1;
		annee =  calendar.get(Calendar.YEAR);
		heure = calendar.get(Calendar.HOUR);
		minute = calendar.get(Calendar.MINUTE);
		seconde = calendar.get(Calendar.SECOND);
		
		System.out.print(jour+"/"+mois+"/"+annee + " ");
		System.out.println(heure+":"+minute+":"+seconde);
		
		System.out.print(Calendar.DAY_OF_WEEK);
		
		

	}

}
