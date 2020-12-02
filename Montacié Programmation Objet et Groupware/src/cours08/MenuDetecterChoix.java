/*
 * Cr�� le 5 janv. 2006
 *
 * Pour changer le mod�le de ce fichier g�n�r�, allez � :
 * Fen�tre&gt;Pr�f�rences&gt;Java&gt;G�n�ration de code&gt;Code et commentaires
 */
package cours08;

import javax.swing.*;
import javax.swing.event.*;

public class MenuDetecterChoix extends JMenuBar implements MenuListener {
	private static final long serialVersionUID = 178;
	private JMenu[] menus = null;
	private int nbMenus;
	/**
	 * @param args
	 */
	public MenuDetecterChoix(String[] nomMenus) {
		nbMenus = nomMenus.length;
		menus = new JMenu[nbMenus];
		for (int i = 0;i < nbMenus;i++) {
			menus[i] = new JMenu(nomMenus[i]);
			add(menus[i]);
			menus[i].addMenuListener(this);
		}

	}

	public void menuSelected(MenuEvent arg0) {
		for (int i = 0;i < nbMenus;i++) {
			if (arg0.getSource() == menus[i])
				System.out.println("menu " + i + " s�lectionné");
		}
		
	}

	public void menuDeselected(MenuEvent arg0) {
		for (int i = 0;i < nbMenus;i++) {
			if (arg0.getSource() == menus[i])
				System.out.println("menu " + i + " d�s�lectionné");
		}
		
	}

	public void menuCanceled(MenuEvent arg0) {
		
	}

}
