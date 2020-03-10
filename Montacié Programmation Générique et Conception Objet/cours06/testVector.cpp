#include <iostream>
#include <vector>
using namespace std;
int main() {
	int tabEnt[] = { 10, 15, 23, 67, 43, 98, 34, 77 };
	vector<int> vi;
	for (int i = 0; i < sizeof(tabEnt) / sizeof(int); i++)
		vi.push_back(tabEnt[i]);

	cout << vi.size() << "  ";
	for (int i = 0; i < vi.size(); i++)
		cout << vi[i] << " ";
}
