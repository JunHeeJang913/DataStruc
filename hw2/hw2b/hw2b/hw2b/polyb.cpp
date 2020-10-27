#include <iostream>
#include "polyb.h"
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
			if(p.termArray[i].exp!=1)
				os<< "^"<<p.termArray[i].exp;
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
	while ((i < this->terms) && (j < b.terms)) {
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

Polynomial Polynomial::operator/(Polynomial& b)
{
	Polynomial c;	
	bool exist=false;
	int maxExp = this->termArray[0].exp;
	float devider = -b.termArray[1].coef;
	float subSum;
	int i = 0; int j = 0; int h = 0;
	//나눗셈에 분배법칙을 적용하려 했으니 될리가 없었다.
	//다행히 분모가 1차로 제한돼있으므로 조립제법을 설계하자.
	for (; i < maxExp ; ++i) {
		if (i == 0) {
			c.NewTerm(this->termArray[i].coef, maxExp - 1);
			subSum = devider * this->termArray[i].coef;
		}
		else {
			for (; j < this->terms; ++j) {
				if (maxExp - i == this->termArray[j].exp) {
					exist = true;
					break;
				}
			}
			if (exist == true) {
				c.NewTerm(this->termArray[i].coef + subSum, maxExp - (i+1));
				subSum = (this->termArray[i].coef + subSum)*devider;
			}
			else if (exist == false) {
				c.NewTerm(subSum, maxExp - (i+1));
				subSum = subSum * devider;
			}
		}
	}
			/*
			for (h = 0; h < c.terms; ++h) {
				if (c.termArray[h].exp == tempExp) {
					plusOrNew = true;
					break;
				}
			}
			if (plusOrNew = false) 
				c.NewTerm(tempCoeff, tempExp);
			else {
				c.termArray[h].coef = c.termArray[h].coef + tempCoeff;
			}*/
	return c;
}