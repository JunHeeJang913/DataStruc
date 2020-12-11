#include "AVL.h"

int Node::calHeight(Node * n){
    if(n!=nullptr){
        n->leftheight=calHeight(this->leftChild);
        n->rightheight=calHeight(this->rightChild);
        height=max(leftheight,rightheight)+1;
    }
    return height;
}

int Node::calBF(){
    this->calHeight();
    balFac=this->leftheight-this->rightheight;
    return balFac;
}

void AVLtree::Search(int a,Node * n){   //a ã���� �ϴ� ��, n�� root���
    Node* curNode;
    curNode=n;
    while(curNode->value!=a){
        cout<<curNode->value<<" -> ";
        if(curNode->value<a)
            curNode=curNode->rightChild;
        else
            curNode=curNode->leftChild;        
    }
    cout<<curNode->value;
}

void AVLtree::insert(int a,Node * &n){
    Node * curNode=n;
    if(root==nullptr)
        root=new Node(a);
    if(n==NULL){
        n=this->root;
        return;
    }
    if(a>curNode->value){
        if(curNode->rightChild=nullptr)
            curNode->rightChild=new Node(a);
        else
            insert(a, curNode->rightChild);
    }
    else{
        if(curNode->leftChild=nullptr)
            curNode->leftChild=new Node(a);
        else
            insert(a, curNode->leftChild);
    }
    //����Լ��̹Ƿ� ������忡 ���� ����� ���������� ���󿡼� ȸ���� �Ͼ
    rotate(curNode->calBF(), n); 
}

void AVLtree::del(int a, Node * n){
    Node * curNode=n;
    static Node * parent;
    static bool check=0;
    if(curNode==nullptr) return;
    if(a==curNode->value){ 
        if(curNode->rightChild==nullptr&&curNode->leftChild==nullptr){
            if(check==0){   //parent�� ���� �ڽ�
                parent->rightChild=nullptr;
            }
            else{
                parent->leftChild=nullptr;
            }
            delete curNode;
        }
        else if(curNode->rightChild==nullptr||curNode->rightChild==nullptr){
            if(check==0)
                parent->rightChild=curNode->rightChild;
            else
                parent->leftChild=curNode->leftChild;
            delete curNode;        
        }
        else{   //������ ���� ū ��带 ����
            Node * parent2;
            parent2=curNode;
            curNode=curNode->leftChild;
            while(curNode->rightChild!=nullptr){
                parent2=curNode;
                curNode=curNode->rightChild;
            }
            parent2->rightChild=nullptr;
            if(check==0){
                curNode->rightChild=parent->leftChild->rightChild; 
                curNode->leftChild=parent->leftChild->leftChild;
                delete parent->leftChild;
                parent->leftChild=curNode;
            }
            else{
                curNode->rightChild=parent->rightChild->rightChild; 
                curNode->leftChild=parent->rightChild->leftChild;
                delete parent->rightChild;
                parent->rightChild=curNode;
            }
        }
    }
    else if(a>curNode->value){
        check=0;
        parent=curNode;
        del(a,curNode->rightChild);
        rotate(n->calBF(), n);
    }
    else{
        check=1;
        parent=curNode;
        del(a,curNode->leftChild);
        rotate(n->calBF(), n);
    }
    
}

void AVLtree::Showresult(Node * n){    
    cout<<n->value;
    if(n->leftChild==nullptr)
        cout<<"\tleft : empty";
    else
        cout<<"\tleft : "<<n->leftChild->value;
    if(n->rightChild==nullptr)
        cout<<"\tright : empty";
    else
        cout<<"\tright : "<<n->rightChild->value;
    cout<<endl;
    if(n->leftChild!=nullptr)
        Showresult(n->leftChild);
    if(n->rightChild!=nullptr)
        Showresult(n->rightChild);
}

void AVLtree::rotate(int key, Node * parent){
    Node * Child;
    if(key>1){//LL�Ǵ� LRȸ��
        if(parent->leftChild->balFac==1){//LLȸ��
            Child=parent->leftChild;
            parent->leftChild=Child->rightChild;
            Child->rightChild=parent;
        }
        else{       //LRȸ��
            Node * grandChild;
            Child=parent->leftChild;
            grandChild=Child->rightChild;
            Child->rightChild=grandChild->leftChild;
            parent->leftChild=grandChild->rightChild;
            grandChild->leftChild=Child;
            grandChild->rightChild=parent;
        }
    }
    else if(key<-1){//RR�Ǵ� RLȸ��
        if(parent->rightChild->balFac==-1){ //RRȸ��
            Child=parent->rightChild;
            parent->rightChild=Child->leftChild;
            Child->leftChild=parent;
        }
        else{       //RL ȸ��
            Node * grandChild;
            Child=parent->rightChild;
            grandChild=Child->leftChild;
            Child->leftChild=grandChild->rightChild;
            parent->rightChild=grandChild->leftChild;
            grandChild->rightChild=Child;
            grandChild->leftChild=parent;
        }
    }
    else{       //ȸ�� ����!
        return;
    }    
}