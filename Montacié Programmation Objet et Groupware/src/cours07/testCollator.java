package cours07;

import com.ibm.icu.text.RuleBasedCollator;
import com.ibm.icu.text.Collator;

public class testCollator {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		RuleBasedCollator rbc1 = null, rbc2 = null;
		try {		 
			String simple = "&9 < a, A < b, B < c, C; ch, cH, Ch, CH < ca; d , D < e, E << �, �, �";
			rbc1 = new RuleBasedCollator(simple);
			
			// ordre lexicographique par d�faut
			rbc2 = (RuleBasedCollator)Collator.getInstance();
		}
		catch (Exception e) {}
		System.out.println(rbc1.getRules());
		
		
		String s1 = "charge", s2 = "casse";
		
		System.out.println(rbc1.compare(s1, s2));
		//		-1	
		System.out.println(rbc2.compare(s1, s2));
		//		1
		
		
	

		 
		
	}

}
