#include <iostream>
#include <list>
#include <queue>
using namespace std;
int main() {
	char tabChr[] = { 'p', 'a', 'r', 'i', 's' };
	queue<char, list<char> > fa;
	for (int i = 0; i < sizeof(tabChr) / sizeof(char); i++)
		fa.push(tabChr[i]);
	while (fa.empty() == false) {
		cout << fa.front() << " ";
		fa.pop();
	}
}
