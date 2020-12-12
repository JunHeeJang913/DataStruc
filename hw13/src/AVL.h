#ifndef AVL_H
#define AVL_H
#include <queue>
#include <stack>
#include <iostream>
using namespace std;
class AVLtree;

class Node{
    friend class AVLtree;
private:
    int value;
    Node * leftChild=nullptr;
    Node * rightChild=nullptr;
    int balFac=0;
    int leftheight=0;
    int rightheight=0;
    int height=0;
    int calHeight(){ return calHeight(this);};
public:
    int calHeight(Node * n);
    int calBF();
    Node(){};
    Node(int a){ value = a; };
    ostream &operator <<(ostream& os){ os<<value; return os; };
};

class AVLtree{
private:
    Node * root=nullptr;
public:
    AVLtree(){};
    void Search(int a,Node * n);
    void insert(int a,Node * &n);
    void del(int a, Node * &n);
    void Showresult(Node * n);
    Node* rotate(int key, Node * n);
    void rotateAll(Node *&n);
};




#endif