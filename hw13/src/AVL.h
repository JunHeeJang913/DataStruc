#ifndef AVL_H
#define AVL_H
#include <iostream>
using namespace std;
class AVLtree;

class Node{
    friend class AVLtree;
private:
    int value;
    Node * leftChild;
    Node * RightChild;
    int leftheight=0;
    int rightheight=0;
public:
    Node();
    Node(int a){ value = a; };
    ostream &operator <<(ostream& os){ os<<value; return os; };
};

class AVLtree{
private:
    Node * root;
public:
    friend class Node;
    void Search(int a,Node * n);
    void insert(int a,Node * n);
    void del(int a, Node * n);
    void Showresult(Node * n);
    void rotate(Node * n);
};




#endif