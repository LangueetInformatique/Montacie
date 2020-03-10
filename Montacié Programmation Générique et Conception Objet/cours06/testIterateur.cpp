#include <iostream>
#include <list>
#include "Date.h"

typedef list<Date> listDate;
typedef listDate::iterator ilistDate;

using namespace std;
int main() {
	listDate L;
	ilistDate it;
	Date today, dfin;

	cin >> today;
	cin >> dfin;
	do {
		L.push_front(today);
		++today;
	} while (today <= dfin);

	// 1ere version
	for (it = L.begin(); it != L.end(); it++)
		cout << *it << " ";
	cout << endl;

	// 2eme version

	it = L.end();
	do {
		--it;
		cout << *it << " ";
	} while (it != L.begin());

	return 0;
}

