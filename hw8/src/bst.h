#include <iostream>
#include <string>
using namespace std;
template <class K, class E>
struct Node
{
    Node(K ky, E el, Node<K, E> *left = 0, Node<K, E> *right = 0) : key(ky), element(el), leftChild(left), rightChild(right) {}
    bool leftThreaded=true;
    Node<K, E> *leftChild;
    K key;
    E element;
    Node<K, E> *rightChild;
    bool rightThreaded=true;
};
template <class K, class E>
class BST
{
public:
    BST() { root = 0; }
    void Insert(K &newkey, E &el) { Insert(root, newkey, el); }
    void Inorder() { Inorder(root); }
    void Delete(K &oldkey) { Delete(root,oldkey); }
    bool Find(const K &, E &);
    void Max();                        // ����
    void Min();                        // ����

private:
    void Visit(Node<K, E> *);
    void Insert(Node<K, E> *&, K &, E &); // ����
    void Inorder(Node<K, E> *);
    void Delete(Node<K, E> *&, K &); // ����
    Node<K, E> *root;
};

template <class K, class E>
void BST<K, E>::Visit(Node<K, E> *ptr)
{
    cout << ptr->key << ':' << ptr->element << ' ';
}

template <class K, class E>
void BST<K, E>::Insert(Node<K,E> *&ptr,K &newkey,E &el){
    static Node<K,E> *temp = 0;
    static bool check = 0;
    static bool visitRoot=false;
    Node<K,E> *tempChild=0;
    if(ptr==root&&visitRoot==false){
        visitRoot=true;
        if(root==0){
            ptr=new Node<K,E>(newkey,el);
            temp=ptr;
        }
        else{
            if (newkey < ptr->key)
            {
                check = 0;
                temp = ptr;
                Insert(ptr->leftChild, newkey,el);
            }
            else if (newkey > ptr->key)
            {
                check = 1;
                temp = ptr;
                Insert(ptr->rightChild, newkey,el);
            }
            else
                ptr->element=el;
        }
    }//��Ʈ
    else if(check==0){
        if(temp->leftThreaded==true){
            tempChild=temp->leftChild;
            ptr=new Node<K,E>(newkey,el);
            ptr->rightChild=temp;
            ptr->leftChild=tempChild;
            temp->leftThreaded=false;
        }
        else{
            if (newkey < ptr->key)
            {
                check = 0;
                temp = ptr;
                Insert(ptr->leftChild, newkey,el);
            }
            else if (newkey > ptr->key)
            {
                check = 1;
                temp = ptr;
                Insert(ptr->rightChild, newkey,el);
            }
            else
                ptr->element=el;

        }
    }//����
    else if(check==1){
        if(temp->rightThreaded==true){
            tempChild=temp->rightChild;
            ptr=new Node<K,E> (newkey,el);
            ptr->leftChild=temp;
            ptr->rightChild=tempChild;
            temp->rightThreaded=false;
        }
        else{
            if (newkey < ptr->key)
            {
                check = 0;
                temp = ptr;
                Insert(ptr->leftChild, newkey,el);
            }
            else if (newkey > ptr->key)
            {
                check = 1;
                temp = ptr;
                Insert(ptr->rightChild, newkey,el);
            }
            else
                ptr->element=el;
        }
    }//����
    visitRoot=false;
}

template <class K, class E>
void BST<K, E>::Delete(Node<K,E> *&ptr,K & key){
    /*
    Ű�� ���� ��, ��������϶�(nonChildNode), �Ƶ��� �ϳ��� ����϶�(one ChildNode)
    �Ƶ��� ���� ��� �϶�(two ChildNodes)-->���� �ִ�, ���� �ּ� �� �ϳ��� ��ü ����
    find�Լ��� �κ��� ��������
    */
    bool isKeyExist=false;
    bool check;
    Node<K,E> *cur=root;//root input
    Node<K,E> *parent;
    while (cur){
        if (key < cur->key){
            check=0;
            parent=cur;
            cur = cur->leftChild;
        }
        else if (key > cur->key){
            check=1;
            parent=cur;
            cur = cur->rightChild;
        }
        else{   //temp�� ����Ű�� ����� key�� �Էµ� key�� ����
            isKeyExist=true;
            break;
        }
    }
    if(isKeyExist==false)
        return;
    else{
        //temp:no Child
        if(cur->leftThreaded==true&&cur->rightThreaded==true){
            if(check==0){
                parent->leftChild=cur->leftChild;
                parent->leftThreaded=true;
            }
            else{
                parent->rightChild=cur->rightChild;
                parent->rightThreaded=true;
            }
            delete cur;                      
        }
        //one Child->�Ѵ� true�� ���� ������ �ٷ�� ������,
        //�ڵ������� �����ϳ��� true�� ��츦 �ٷ��.
        else if(cur->leftThreaded==true||cur->rightThreaded==true){
            if(check==0)
                parent->leftChild=cur->leftChild;
            else
                parent->rightChild=cur->rightChild;
            delete cur;
        }
        //two ChildNodes
        else{
            //���� ���� ū ���!
            Node<K,E> *parent2;
            parent2=cur;
            cur=cur->leftChild;
            while(cur->rightThreaded!=true){
                parent2=cur;
                cur=cur->rightChild;
            }
            parent2->rightChild=cur->rightChild;
            parent2->rightThreaded=cur->rightThreaded;
            if(check==0){
                cur->rightChild=parent->leftChild->rightChild; 
                cur->leftChild=parent->leftChild->leftChild;
                cur->rightThreaded=parent->leftChild->rightThreaded;
                cur->leftThreaded=parent->leftChild->leftThreaded;
                delete parent->leftChild;
                parent->leftChild=cur;
            }
            else{
                cur->rightChild=parent->rightChild->rightChild; 
                cur->leftChild=parent->rightChild->leftChild;
                cur->rightThreaded=parent->rightChild->rightThreaded;
                cur->leftThreaded=parent->rightChild->leftThreaded;
                delete parent->rightChild;
                parent->rightChild=cur;
            }
        }
        return;
    }

}

template <class K, class E>
void BST<K, E>::Max(){
    Node<K,E> *tempMax=root;
    while(tempMax->rightChild!=0){
       tempMax=tempMax->rightChild;
    }
    cout<<"Maxmum Value is "<<tempMax->key<<" : "<<tempMax->element<<endl;    
    return;
}

template <class K, class E>
void BST<K, E>::Min(){
    Node<K,E> *tempMin=root;
    while(tempMin->leftChild!=0){
        tempMin=tempMin->leftChild;
    }
    cout<<"Minimum Value is "<<tempMin->key<<" : "<<tempMin->element<<endl;  
    return;
}

template <class K, class E>
void BST<K, E>::Inorder(Node<K, E> *currentNode)
{
    Node<K,E> *cN=root;
    static bool visitRoot=false;
    while(cN->rightChild!=0){
        Node<K,E> * temp;
        if(visitRoot==false){
            temp=cN;
            visitRoot=true;
        }
        else
            temp=cN->rightChild;       
        if(!cN->rightThreaded)
            while(!temp->leftThreaded)temp=temp->leftChild;
        cN=temp;
        Visit(cN);
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
            if(temp->rightThreaded==false)
                temp = temp->rightChild;
            else
                break;
        }
        else if (k < temp->key)
        {
            if(temp->leftThreaded==false)
                temp = temp->leftChild;
            else
                break;
        }
        else
        {
            e = temp->element;
            return true;
        }
    }
    return false;
}