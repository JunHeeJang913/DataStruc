#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

void getdata(istream&, int&, int&); 
void Path(int, int);    //getdata�� Path�� maze.cpp�� ����.

int main(int argc, char* argv[]){      
    /*  
        argc:argument�� ��
        argv[0]:�����̸���, argv[n(n!=0)]:argument�� ������ ��
    */
    int m, p; // m by p maze
    if (argc == 1)
        cerr << "Usage: " << argv[0] << " maze_data_file" << endl;
    else {
        ifstream is(argv[1]);
        if (!is) { cerr << argv[1] << " does not exist\n"; exit(1); }  
        cout << "For maze datafile (" << argv[1] << ")\n";
        getdata(is, m, p);      //
        is.close();     //�Է¿Ϸ�
        Path(m, p);     //��°���=>���� ����� ���
    }
}
/*
�������
For maze datafile (maze.in)
-> (1,1) -> (2,2) -> (1,3) -> (1,4) -> (1,5)
-> (2,4) -> (3,5) -> (3,4) -> (4,3) -> (5,3)
-> (6,2) -> (7,2) -> (8,1) -> (9,2) -> (10,3)
-> (10,4) -> (9,5) -> (8,6) -> (8,7) -> (9,8)
-> (10,8) -> (11,9) -> (11,10) -> (10,11) -> (10,12)
-> (10,13) -> (9,14) -> (10,15) -> (11,15) -> (12,15)*/