#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
using namespace std;
template <class T>
struct Node
{
    Node(T d, Node<T> *left = 0, Node<T> *right = 0)
        : data(d), leftChild(left), rightChild(right) {}
    Node<T> *leftChild;
    T data;
    Node<T> *rightChild;
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
    if (ptr == 0)
        ptr = new Node<T>(value);
    else if (value < ptr->data)
        Insert(ptr->leftChild, value);
    else if (value > ptr->data)
        Insert(ptr->rightChild, value);
    else
        cout << endl
             << "Duplicate value " << value << " ignored\n";
}

template <class T>
void Tree<T>::Preorder(Node<T> *ptr){

}

template <class T>
void Tree<T>::Inorder(Node<T> *ptr){

}

template <class T>
void Tree<T>::Postorder(Node<T> *ptr){

}

template <class T>
void Tree<T>::Levelorder(){

}
//Preorder, Inorder, Postorder 함수를 구현하시오......
//Levelorder(교재 p266 참조하되 STL 큐를 이용) 를 구현하시오.
#endif