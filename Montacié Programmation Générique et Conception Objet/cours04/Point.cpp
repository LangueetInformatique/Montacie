#include <iostream> // declaration des flots standard
using namespace std;

template <typename T=float> class Point {
	private:
	T abscisse, ordonnee;
	public:
	Point(T a, T b);
	};
	
template <typename T> Point<T>::Point(T a, T b) {
	abscisse = a;
	ordonnee = b;
}

int main() {
	Point<> p1(2,3);
	Point<int> p2(2,3);
}
