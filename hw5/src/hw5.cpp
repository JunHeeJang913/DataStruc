#include <iostream>
#include "GenList.h"
using namespace std;
int main()
{
    GenList Inlist;
    Inlist.Make();  //범용리스트 생성
    Inlist.Print(); //범용리스트 출력
    while (1)
    {
        /*
            1 : Insert
            2 : Delete
            3 : Print
            4 : 종료
        */
        int select;
        cin >> select;
        char i, j;
        if (select == 1)
        {
            cin >> i >> j;
            Inlist.Insert(i, j);
        }
        else if (select == 2)
        {
            cin >> i;
            Inlist.Delete(i);
        }
        else if (select == 3)
        {
            Inlist.Print();
        }
        else if (select == 4)
        {
            break;
        }
        else
        {
            cout << "Wrong Command" << endl;
        }
    }
}