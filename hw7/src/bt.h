#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <class T>
struct Node
{
    Node(T d, Node<T> *left = 0, Node<T> *right = 0)
        : data(d), leftChild(left), rightChild(right) {}
    bool leftThreaded=true;
    Node<T> *leftChild;
    T data;
    Node<T> *rightChild;
    bool rightThreaded=true;
};
template <class T>
class Tree
{
public:
    Tree() { root = 0; } // empty tree
    void Insert(T &value) { Insert(root, value); }
    void Preorder() { Preorder(root); }
    void Inorder() { Inorder(root); }
    void Postorder() { Postorder(root); }
    void Levelorder();

private: // helper 함수들
    void Visit(Node<T> *);
    void Insert(Node<T> *&, T &);
    void Preorder(Node<T> *);
    void Inorder(Node<T> *);
    void Postorder(Node<T> *);
    Node<T> *root;
};
template <class T>
void Tree<T>::Visit(Node<T> *ptr) { cout << ptr->data << " "; }
template <class T>
void Tree<T>::Insert(Node<T> *&ptr, T &value)
{ //Insert 의 helper 함수
    static Node<T> *temp = 0;
    static bool check = 0;
    static bool visitRoot=false;
    Node<T> *tempChild=0;
    //리프노트일때VS리프노트가 아닐때-->이 조건이 무엇인가??
    if(ptr==root&&visitRoot==false){
        visitRoot=true;
        if(root==0){
            ptr=new Node<T>(value);
            temp=ptr;
        }
        else{
            if (value < ptr->data)
            {
                check = 0;
                temp = ptr;
                Insert(ptr->leftChild, value);
            }
            else if (value > ptr->data)
            {
                check = 1;
                temp = ptr;
                Insert(ptr->rightChild, value);
            }
            else
                cout << "Duplicate value " << value << " ignored\n" << endl;
        }
    }//루트
    else if(check==0){
        if(temp->leftThreaded==true){
            tempChild=temp->leftChild;
            ptr=new Node<T>(value);
            ptr->rightChild=temp;
            ptr->leftChild=tempChild;
            temp->leftThreaded=false;
        }
        else{
            if (value < ptr->data)
            {
                check = 0;
                temp = ptr;
                Insert(ptr->leftChild, value);
            }
            else if (value > ptr->data)
            {
                check = 1;
                temp = ptr;
                Insert(ptr->rightChild, value);
            }
            else
                cout << "Duplicate value " << value << " ignored\n" << endl;

        }
    }//좌측
    else if(check==1){
        if(temp->rightThreaded==true){
            tempChild=temp->rightChild;
            ptr=new Node<T> (value);
            ptr->leftChild=temp;
            ptr->rightChild=tempChild;
            temp->rightThreaded=false;
        }
        else{
            if (value < ptr->data)
            {
                check = 0;
                temp = ptr;
                Insert(ptr->leftChild, value);
            }
            else if (value > ptr->data)
            {
                check = 1;
                temp = ptr;
                Insert(ptr->rightChild, value);
            }
            else
                cout << "Duplicate value " << value << " ignored\n" << endl;
        }
    }//우측
    visitRoot=false;
}


template <class T>
void Tree<T>::Preorder(Node<T> *ptr){
    if(ptr){
        Visit(ptr);
        if(ptr->leftThreaded==false)
            Preorder(ptr->leftChild);
        if(ptr->rightThreaded==false)
            Preorder(ptr->rightChild);
    }
}//재귀적인 방법

template <class T>
void Tree<T>::Inorder(Node<T> *ptr){
    //비재귀적 원본
    /*stack<Node<T>*> s;
    Node<T> * currentNode = root;
    while(1){
        while(currentNode){
            s.push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if(s.empty())   return;
        currentNode = s.top(); s.pop();
        Visit(currentNode);
        currentNode = currentNode->rightChild;
    }*/
    Node<T> *temp
}//비재귀적방법

template <class T>
void Tree<T>::Postorder(Node<T> *ptr){
    if(ptr){
        if(ptr->leftThreaded==false)
            Postorder(ptr->leftChild);
        if(ptr->rightThreaded==false)
            Postorder(ptr->rightChild);
        Visit(ptr);
    }
}

template <class T>
void Tree<T>::Levelorder(){
    queue<Node<T>*> q;
    Node<T> * currentNode=root;
    while(currentNode){
        Visit(currentNode);
        if(currentNode->leftChild&&currentNode->leftThreaded==false){
            q.push(currentNode->leftChild);
        }
        if(currentNode->rightChild&&currentNode->rightThreaded==false){
            q.push(currentNode->rightChild);
        }
        if(q.empty())   return;
        currentNode=q.front(); q.pop(); 
    }
}
//Preorder, Inorder, Postorder 함수를 구현하시오......
//Levelorder(교재 p266 참조하되 STL 큐를 이용) 를 구현하시오.
#endif