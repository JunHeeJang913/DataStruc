#include <iostream>
#include <cstring>
#include "mystr.h"
using namespace std;
Mystring::Mystring(const char* str = "default") {
	len = strlen(str);
	string = new char[len + 1];
	strcpy(string, str);
}
//_Done_
bool Mystring::operator ==(const Mystring& str) {
	if (strcmp(this->string , str.string) == 0) return true;
	else return false;
}

//_Done_
Mystring& Mystring::operator =(const Mystring& str) {
	if (this->string != NULL)
		delete[] this->string;
	this->len = str.len;
	this->string = new char[this->len + 1];
	strcpy(this->string, str.string);
	return *this;
}

//  아마도 * 안에서 오류가 생기는 것 같습니다.
Mystring Mystring ::operator *(const Mystring& str) {
	int i,j;
	int length = this->len + str.len + 1;
	char *tempchar = new char[length];
	//문자열의 길이를 기준으로 두가지 경우로 나눴습니다.
	if (this->len >= str.len) {					// 번갈아가며 대입하고,		
		for (i = 0; i < str.len; ++i) {
			tempchar[2*i] = this->string[i];
			tempchar[2*i + 1] = str.string[i];
			j = 2*(i+1);
		}
		for (; i < this->len; ++i) {		//남은 문자열을 대입합니다.
			tempchar[j++] = this->string[i];
		}
		Mystring tempstring = tempchar;
		delete[] tempchar;			
		*this = tempstring;
		return *this;
	}
	else {
		for (i = 0; i < this->len; ++i) {
			tempchar[2 * i] = this->string[i];
			tempchar[2 * i + 1] = str.string[i];
			j = 2 * (i + 1);
		}
		for (; i < str.len; ++i) {
			tempchar[j++] =str.string[i];
		}
		Mystring tempstring = tempchar;
		delete[] tempchar;
		*this = tempstring;
		
		return *this;
	}
}//_Done..?_
Mystring Mystring::operator +(const Mystring &str) {
	int length = this->len + str.len + 1;
	char* tempchar = new char[length];
	strcpy(tempchar, this->string);
	strcat(tempchar, str.string);
	Mystring tempstring(tempchar);
	delete[] tempchar;
	return tempstring;
}

//________________________________Done_____________________________
ostream& operator <<(ostream& out, const Mystring& str) {
	out << str.string;
	return out;
}
Mystring::~Mystring() { delete[] string; }