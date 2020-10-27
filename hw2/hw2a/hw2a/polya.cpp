#include <iostream>
#include "polya.h"
using namespace std;
istream& operator>> (istream& is, Polynomial& p) {
	int noofterms; float coef; int exp;
	is >> noofterms;
	for (int i = 0; i < noofterms; i++) {
		is >> coef >> exp;
		p.NewTerm(coef, exp);
	}
	return is;
}
//위와 같이 출력시 지수가 0 이 아닌 항의 경우 그 계수가 1 이면 출력을 생략하고 ,- 1 이면 -로 출력 할것 지키지 아니할시 감점
ostream& operator<< (ostream& os, Polynomial& p) {
	for (int i = 0; i < p.terms; ++i) {
		if ((p.termArray[i].coef != 0) && (p.termArray[i].coef != 1)) {
			if (p.termArray[i].coef == -1)
				os << "-";
			else
				os << p.termArray[i].coef;
		}
		if (p.termArray[i].exp != 0) {
			os << "x";
			if (p.termArray[i].exp != 1)
				os << "^" << p.termArray[i].exp;
		}
		if (i + 1 < p.terms) {
			if (p.termArray[i + 1].coef >= 0)
				os << "+";
			else if (p.termArray[i + 1].coef)
				os << "";
		}
	}
	os << endl;
	return os;
}
Polynomial::Polynomial() :capacity(1), terms(0) {
	termArray = new Term[capacity];
}
void Polynomial::NewTerm(const float theCoeff, const int theExp) {
	if (this->terms == this->capacity) {
		this->capacity += 1;
		Term*tempTerm = new Term[capacity];
		for (int i = 0; i < terms; ++i) {
			tempTerm[i] = this->termArray[i];
		}
		delete[] termArray;
		this->termArray = tempTerm;
	}
	this->termArray[this->terms].coef = theCoeff;
	this->termArray[this->terms++].exp = theExp;
}
Polynomial Polynomial::operator+(Polynomial& b) {
	Polynomial tempPoly; int i = 0; int j = 0; float c = 0;
	while ((i <this->terms) && (j < b.terms)){
		if (this->termArray[i].exp == b.termArray[j].exp) {
			c = this->termArray[i].coef + b.termArray[j].coef;
			if (c != 0) tempPoly.NewTerm(c, this->termArray[i].exp);
			i++; j++;
		}
		else if (this->termArray[i].exp > b.termArray[j].exp) {
			tempPoly.NewTerm(this->termArray[i].coef, this->termArray[i].exp);
			i++;
		}
		else if (this->termArray[i].exp < b.termArray[j].exp) {
			tempPoly.NewTerm(b.termArray[j].coef, b.termArray[j].exp);
			j++;
		}
	}
	for (; i < this->terms; ++i) {
		tempPoly.NewTerm(this->termArray[i].coef, this->termArray[i].exp);
	}
	for (; j < b.terms; ++j) {
		tempPoly.NewTerm(b.termArray[j].coef, b.termArray[j].exp);
	}
	return tempPoly;
}
