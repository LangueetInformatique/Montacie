package cours08;

import javax.swing.*;

import java.awt.*;

/**
 * @author montacie
 */
public class testControleSaisie {

	public static void main(String[] args) {
		JFrame fen = new JFrame("Exemples de composants graphiques atomiques");
		fen.setSize(500, 500);
		JPanel p = new JPanel();
		fen.getContentPane().add(p);  
		p.setLayout(new GridLayout(3,3));
		 
		
//		   D�claration des composants        
		JButton bt = new JButton("rectangle � cliquer");
		JRadioButton rbt = new JRadioButton("rectangle � cliquer avec m�moire");
		JCheckBox cb = new JCheckBox("case � cocher");
		JLabel lb = new JLabel("affichage d�un texte dans un composant");
		JTextField tf = new JTextField("ligne de saisie texte");
		JTextArea ta = new JTextArea("champ multi-ligne de saisie texte");
		JPasswordField pf = new JPasswordField("champ de saisie d�un mot de passe");
		String chx[] = {"choix1", "choix2", "choix3"}; 
		JList ls = new JList(chx); JComboBox cbo = new JComboBox(chx);

//		   Ajouts des composants � la JFrame        
		p.add(bt); p.add(rbt); p.add(cb); p.add(lb);p.add(tf); p.add(ta); p.add(pf); p.add(ls); p.add(cbo);
        
		fen.setVisible(true);

	}
}
