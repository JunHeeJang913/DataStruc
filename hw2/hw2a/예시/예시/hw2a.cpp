#include <iostream>

#include "polya.h"

using namespace std;

 

int main(void)

{

        Polynomial p1, p2;

 

        cin >> p1 >> p2; //2���� ���׽��� �о���δ�

        Polynomial p3 = p1 + p2;

        cout << p1 << p2 << p3;

        return 0;

}

