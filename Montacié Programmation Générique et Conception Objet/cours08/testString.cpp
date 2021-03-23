#include <iostream>
#include <string>
using namespace std;


int main()
{
string s1(10, 'a'), s2(" la fille du roi zoulou. ");
cout << s1 << s2 << endl;
// aaaaaaaaaa la fille du roi zoulou. 

string s3(s2), s4(s2, 1, 4); cout << s3 << s4 << endl;
//  la fille du roi zoulou. la f

cout << s3.find("roi") << endl; 
// 13
cout << s3.find_first_of("aeiou") << endl; 
// 2

s2.insert(s3.find("fille"), "grande ");
cout << s2 << endl; 
// la grande fille du roi zoulou. 

s3.replace(1, 8 ,"le fils");
cout << s3 << endl; 
// le fils du roi zoulou.
} 
