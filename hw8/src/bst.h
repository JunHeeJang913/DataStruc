#include <iostream>
#include <string>
using namespace std;
template <class K, class E>
struct Node
{
    Node(K ky, E el, Node<K, E> *left = 0, Node<K, E> *right = 0) : key(ky), element(el), leftChild(left), rightChild(right) {}
    Node<K, E> *leftChild;
    K key;
    E element;
    Node<K, E> *rightChild;
};
template <class K, class E>
class BST
{
public:
    BST() { root = 0; }
    void Insert(K &newkey, E &el) { Insert(root, newkey, el); }
    void Inorder() { Inorder(root); }
    void Delete(K &oldkey) { Delete(root, root, oldkey); }
    bool Find(const K &, E &);

private:
    void Visit(Node<K, E> *);
    void Insert(Node<K, E> *&, K &, E &); // 备泅
    void Inorder(Node<K, E> *);
    Node<K, E> *Delete(Node<K, E> *&, Node<K, E> *&, K &); // 备泅
    Node<K, E> *Max(Node<K, E> *&);                        // 备泅
    Node<K, E> *Min(Node<K, E> *&);                        // 备泅
    Node<K, E> *root;
};
template <class K, class E>
void BST<K, E>::Visit(Node<K, E> *ptr)
{
    cout << ptr->key << ':' << ptr->element << ' ';
}
template <class K, class E>
void BST<K, E>::Inorder(Node<K, E> *currentNode)
{
    if (currentNode)
    {
        Inorder(currentNode->leftChild);
        Visit(currentNode);
        Inorder(currentNode->rightChild);
    }
}
template <class K, class E>
bool BST<K, E>::Find(const K &k, E &e)
{
    Node<K, E> *temp = root;
    while (temp)
    {
        if (k > temp->key)
        {
            temp = temp->rightChild;
        }
        else if (k < temp->key)
        {
            temp = temp->leftChild;
        }
        else
        {
            e = temp->element;
            return true;
        }
    }
    return false;
}