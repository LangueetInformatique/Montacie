#include <iostream>
#include <deque>
#include "Date.h"

using namespace std;
int main() {
	deque<Date> dd;
	Date today, dfin;

	cin >> today;
	cin >> dfin;
	do {
		today++;
		dd.push_front(today);
	} while (today < dfin);

	cout << dd.size() << "  ";
	for (int i = 0; i < dd.size(); i++)
		cout << dd[i] << " ";
}
