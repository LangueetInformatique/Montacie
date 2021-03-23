#ifndef DATE_H_
#define DATE_H_

#include <iostream>			// declaration des flots standard
using namespace std;

class Date {
private:
	int jour, mois, annee;

public:
	Date();

	Date(int j, int m, int a);

	void incrementer();
	void afficher();
	void saisir();

	// acesseurs possibilite de declarer la fonction directement dans le
	//.h quand les methodes sont tres courte : ligne

	int getjour() const;	//{return jour;}
	int getmois() const;	//{return mois;}
	int getannee() const;	//{return mois;}

	friend istream & operator >>(istream & S, Date & y);
	friend ostream & operator <<(ostream & S, const Date & y);
	bool operator < (const Date & y) const;
	bool operator != (const Date & y) const;
	void operator ++ ();
};

#endif /*DATE_H_*/
