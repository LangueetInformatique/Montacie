package atelier12;

public class testMultiFenetre {

	public static void main(String[] args) {

		MultiFenetre mf = new MultiFenetre(2);
		mf.affichertxt(
				"Après plus de six semaines de course, le skippeur Yannick Bestaven s’est installé en tête du Vendée Globe, mercredi 16 décembre, alors qu’il navigue aux portes de l’océan Pacifique, qui sera pour lui une découverte.",
				0);

		mf.affichertxt(
				"Et comme une bonne nouvelle n’arrive jamais seule, Yannick Bestaven a reçu une compensation horaire de dix heures et quinze minutes pour s’être dérouté afin de venir aider au sauvetage de Kevin Escoffier",
				1);
	}

}
