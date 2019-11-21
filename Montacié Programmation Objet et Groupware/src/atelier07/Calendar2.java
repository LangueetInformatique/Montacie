package atelier07;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;

public class Calendar2 extends GregorianCalendar {
	private boolean cours;
	private int  jourS, heure, minute, seconde; 

	
	public Calendar2() {
		
	}

	/** l'attribut cours est mis à vrai si l'objet est créé pendant la période jeudi (9h30-12h)
	 * 
	 */
	public Calendar2(TimeZone zone) {
		super(zone);
		this.setTime(new Date());
		jourS = this.get(Calendar.DAY_OF_WEEK);
		heure = this.get(Calendar.HOUR);
		minute = this.get(Calendar.MINUTE);
		seconde = this.get(Calendar.SECOND);
		cours = verification();
	}
	
	private boolean verification() {
		if (jourS != 5) return false;
		if ((heure == 10) || (heure == 11)) return true;
		if ((heure == 9) && (minute > 30)) return true;
		return false;
		}
	
	public boolean cours() {
		return cours;
	}

	public Calendar2(Locale aLocale) {
		super(aLocale);
		// TODO Auto-generated constructor stub
	}

	public Calendar2(TimeZone zone, Locale aLocale) {
		super(zone, aLocale);
		// TODO Auto-generated constructor stub
	}

	public Calendar2(int year, int month, int dayOfMonth) {
		super(year, month, dayOfMonth);
		// TODO Auto-generated constructor stub
	}

	public Calendar2(int year, int month, int dayOfMonth, int hourOfDay, int minute) {
		super(year, month, dayOfMonth, hourOfDay, minute);
		// TODO Auto-generated constructor stub
	}

	public Calendar2(int year, int month, int dayOfMonth, int hourOfDay, int minute, int second) {
		super(year, month, dayOfMonth, hourOfDay, minute, second);
		// TODO Auto-generated constructor stub
	}

}
