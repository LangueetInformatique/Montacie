package atelier11;

import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Partie2 extends JFrame{
	
	/*
	 * Les classes de type Layout font partie du package java.awt. 
	 * Donner la liste des classes de type Layout.
	 */
	
	/* liste des classes java.awt : color, font, list, desktop, alpharcompositf, dnd, event, geom, im, peer, etc.
	
	/* Liste des classes de type Layout : 
	 * Layout 
	 * FlowLayout 	
	 * BorderLayout
	 * GridLayout
	 */

	/* 
	 * Créer un plan de la salle D219 sous la forme d’une grille 5x4 en indiquant les emplacements de chaque étudiant. 
	 * 
	 * Ajouter sur le référentiel le fichier listeEtudiants contenant vos noms, prénoms et emplacement sur le plan
	 * 
	 */
	GridLayout salle219 = new GridLayout(5, 4);
	
	public Partie2() {
	JFrame frame = new JFrame();
    frame.setVisible(true);
    JPanel panel = new JPanel();
    frame.setContentPane(panel);
    panel.setLayout(salle219);
    
    panel.add(new JButton("Julien"));
    panel.add(new JButton("Ana"));
    panel.add(new JButton("Chengwanli"));
    panel.add(new JButton("Mustapha"));
    panel.add(new JButton("Alexane"));
    panel.add(new JButton("Morgann"));
	}
}
