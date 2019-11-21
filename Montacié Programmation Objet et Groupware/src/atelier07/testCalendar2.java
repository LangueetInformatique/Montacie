package atelier07;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.SimpleTimeZone;
import java.util.TimeZone;

public class testCalendar2 {

	public static void main(String[] args) {
		// get the supported ids for GMT+01:00 (Heure d'Hiver en France)
				String[] ids = TimeZone.getAvailableIDs(1 * 60 * 60 * 1000);
				// if no ids were returned, something is wrong. get out.
				if (ids.length == 0)
					System.exit(0);

				// create a Heure d'Hiver en France time zone
				SimpleTimeZone pdt = new SimpleTimeZone(1 * 60 * 60 * 1000, ids[0]);
				Calendar2 calendar = new Calendar2(pdt);
				System.out.println(calendar.cours());
				calendar.creation();
				calendar.afficher();

	}

}
