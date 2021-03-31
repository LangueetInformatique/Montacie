package cours09;

public class ChargementPilote {
    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.jdbc.Driver").newInstance();
        } catch (Exception ex) {
        	System.out.println("Erreur de chargement du pilote");
        }
    }
}
