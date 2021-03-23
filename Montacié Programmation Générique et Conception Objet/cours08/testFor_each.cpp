#include <iostream>
#include <functional>
#include <deque>
#include "../tp03/Date.h"
using namespace std;

template<typename T> class ecrire {
private:
  int count;
  ostream& os;
public:
  ecrire(ostream& out) : os(out), count(0) { }
  void operator() (T x) { os << x << ' '; ++count; }
  int getcount() { return count; }
};

int main()
{
	deque <Date> dd;
	Date today, dfin;
	
	cin >> today;
	cin >> dfin;
	do {
		++today;
		dd.push_front(today);
	}
	while (today < dfin);
	
  ecrire<Date> ED = for_each(dd.begin(), dd.end(), ecrire<Date>(cout));
  cout << endl << ED.getcount() << " objets ecrits." << endl;
}

