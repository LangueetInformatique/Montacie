package atelier07;

import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;

public class Calendar2 extends GregorianCalendar {
	
	boolean cours;

	/** l'attribut cours est mis à vrai si l'objet est créé pendant la période jeudi (9h30-12h)
	 * 
	 */
	public Calendar2() {
		
	}

	public Calendar2(TimeZone zone) {
		super(zone);
		// TODO Auto-generated constructor stub
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
