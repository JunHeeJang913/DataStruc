#include <iostream>
#include "mystr.h"
using namespace std;
int main() {
	Mystring s1 = "aa";
	Mystring s2 = "z";
	Mystring s3 = "aza";
	Mystring s4 = " ihing";
	Mystring s5 = "fgt";
	s2 = s1 * s2;
	if (s3 == s2)
		cout << s2 +s3+s4*s5<< endl;
}