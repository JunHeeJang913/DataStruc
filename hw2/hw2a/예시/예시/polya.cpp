#include <iostream>
#include "polya.h"
using namespace std;
Polynomial::Polynomial() :capacity(1), terms(0)
{
	termArray = new Term[capacity];
}
void Polynomial::NewTerm(const float theCoeff, const int theExp){

        //Add a new term to the end of termArra
        if (terms == capacity)
        {
               //double capacity of termArray
               capacity *= 2;
               Term *temp = new Term[capacity]; //new array
			   copy(termArray, termArray + terms, temp);
               delete[]termArray; //deallocate old memory
               termArray = temp;
        }
        termArray[terms].coef = theCoeff;
        termArray[terms++].exp = theExp;

}

 

Polynomial Polynomial::operator+(Polynomial &b)
{
        //Return the sum of the polynomials *this and b
        Polynomial c;
       int aPos = 0, bPos = 0;
       while ((aPos < terms) && (bPos < b.terms))
        {
              if (termArray[aPos].exp == b.termArray[bPos].exp)

               {
                      float t = termArray[aPos].coef + b.termArray[bPos].coef;
                      if (t)
                             c.NewTerm(t, termArray[aPos].exp);
                      aPos++;
                      bPos++;
               }

               else if (termArray[aPos].exp < b.termArray[bPos].exp)

               {
				        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

                       bPos++;

               }

               else

               {

                       c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);

                       aPos++;

               }

        }

        //add in remaining term of *this

        for (;aPos < terms;aPos++)

               c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);

        //add in remaining terms of b(x)

        for (;bPos < b.terms;bPos++)

               c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

        return c;

}

 

istream &operator>>(istream &is, Polynomial &p)

{

        //terms and (coefficient, exponent)의 pair들을 읽어들인다

        //높은 차수의 항부터 저장되었다고 가정한다

        int noofterms;

        float coef;

        int exp;;

        is >> noofterms;

        for (int i = 0; i < noofterms; i++)

        {

               is >> coef >> exp; //계수와 지수 pair를 읽어들인다

               p.NewTerm(coef, exp);

        }

        return is;

}

 

ostream &operator<<(ostream &os, Polynomial &p)

{

        for (int i = 0; i < p.terms; i++)

        {

               if (p.termArray[i].coef && p.termArray[i].coef != 1 && p.termArray[i].coef != -1)

                       os << p.termArray[i].coef;

               if(p.termArray[i].exp!=0)

                       os << "x^";

               if(p.termArray[i].exp && p.termArray[i].exp!=1)

                       os<< p.termArray[i].exp;

               if (i != p.terms - 1 && p.termArray[i + 1].coef >= 0)

                       os << " +";

               else if (p.termArray[i + 1].coef == -1)

                       os << " -";

               else if (p.termArray[i + 1].coef < -1)

                       os << " ";

        }

        os << endl;

        return os;

}

