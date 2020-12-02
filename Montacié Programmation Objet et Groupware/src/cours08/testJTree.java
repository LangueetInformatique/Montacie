package cours08;

import javax.swing.*;
import javax.swing.tree.*;
import java.awt.*;

/**
 * @author montacie
 */
public class testJTree {

	public static void main(String[] args) {
		DefaultMutableTreeNode root, tn[];
		String[] ts = 
		{"NP", "NP0", "Det", "the", "N", "boy", "VP", "V", "delivers"};
		tn = new DefaultMutableTreeNode[ts.length];
		
		//	cr�ation des noeuds
		root = new DefaultMutableTreeNode("S");
		for (int i = 0;i < ts.length;i++)
		tn[i] = new DefaultMutableTreeNode(ts[i]);
		
		// cr�ation des liens entre noeuds
		root.add(tn[0]);
		tn[0].add(tn[1]); tn[1].add(tn[2]);tn[2].add(tn[3]);
		tn[1].add(tn[4]);tn[4].add(tn[5]);
		root.add(tn[6]);
		tn[6].add(tn[7]); tn[7].add(tn[8]);
		
		
		//	affichage de l'arbre
		JTree jt = new JTree(root);
		JScrollPane treeView = new JScrollPane (jt);

		JFrame fen = new JFrame("Affichage d'un arbre"); fen.setSize(500, 100);
		Container cpfen = fen.getContentPane(); 
		cpfen.add(treeView);
		fen.setVisible(true);
		
		
		
	}
}
