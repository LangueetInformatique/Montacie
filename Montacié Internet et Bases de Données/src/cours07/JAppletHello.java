
package cours07;

import javax.swing.*;
import java.awt.*;

public class JAppletHello extends JApplet {
	private JPanel jp;
	protected int n = 0;
	   public void init (){ 
		   jp = new JPanel();
		   jp.setBackground(Color.blue);
		   jp.add(new JLabel(getParameter("text")));
		   getContentPane().add(jp);
	     } 
	    public void start() {
	    	jp.add(new JLabel(Integer.toString(n++)));
	    }
	    public void stop() {
	    }
	    public void destroy() {}

}
