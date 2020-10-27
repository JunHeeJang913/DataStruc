#ifndef GENLIST_H
#define GENLIST_H
using namespace std;
class GenList;
class GenListNode{ //범용리스트 노드
    friend class GenList;
public:
    GenListNode(bool t = false, GenListNode *n = NULL) : tag(t), next(n), data(0) {}      
private:
    GenListNode *next;
    bool tag;
    union {
        char data;      //값을 가짐
        GenListNode *down;      //원소가 리스트를 가리킴
    };
};
class GenList{
public:
    GenList() { first = NULL; }     //생성자
    void Make() { //Make driver
        char a;
        cin >> a; //첫 ( 는 생략
        Make(first);
    }
    void Print() { //Print driver
        cout << "(";
        Print(first);
        cout << endl;
    }
    void Insert(char i, char j) { //Insert driver
        Insert(first, i, j);
    }
    void Delete(char i)  { //Delete driver
         Delete(first, i);
    }

private:
    GenListNode *first;
    void Make(GenListNode *&);
    void Print(GenListNode *&);
    void Insert(GenListNode *&, char, char);
    void Delete(GenListNode *&, char);
};
#endif