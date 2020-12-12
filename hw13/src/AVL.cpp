#include "AVL.h"

int Node::calHeight(Node * n){
    if(n!=nullptr){
        n->leftheight=calHeight(n->leftChild);
        n->rightheight=calHeight(n->rightChild);
        n->height=max(n->leftheight,n->rightheight)+1;
    }
    if(n==nullptr) return 0;
    return n->height;
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
    cout<<curNode->value<<endl;
}

void AVLtree::insert(int a,Node * &n){
    Node * curNode=n;
    if(root==nullptr)
        root=new Node(a);
    if(n==NULL){
        curNode=this->root;
        n=curNode;
        return;
    }
    if(a>curNode->value){
        if(curNode->rightChild==nullptr)
            curNode->rightChild=new Node(a);
        else
            insert(a, curNode->rightChild);
    }
    else{
        if(curNode->leftChild==nullptr)
            curNode->leftChild=new Node(a);
        else
            insert(a, curNode->leftChild);
    }
    //����Լ��̹Ƿ� ������忡 ���� ����� ���������� ���󿡼� ȸ���� �Ͼ
    n=rotate(n->calBF(), n); 
}

void AVLtree::del(int a, Node * &n){
    Node * curNode=n;
    static Node * parent;
    static bool check=0;
    if(curNode==nullptr) return;
    if(a==curNode->value){ 
        if(curNode==root){      //root����϶�
            if(curNode->rightChild==nullptr&&curNode->leftChild==nullptr){
                delete curNode; curNode=nullptr;
            }
            else if(curNode->rightChild==nullptr||curNode->rightChild==nullptr){
                if(curNode->rightChild==nullptr)
                    root=curNode->leftChild;
                else
                    root=curNode->rightChild;
                delete curNode; curNode=nullptr;
            }
            else{   //���� �͵� �� ����ū ���->��Ʈ���
                Node * parent2;
                Node * temp=root;
                parent2=curNode;
                curNode=curNode->leftChild;
                while(curNode->rightChild!=nullptr){
                    parent2=curNode;
                    curNode=curNode->rightChild;
                }
                if(curNode->leftChild!=nullptr)
                    parent2->rightChild=curNode->leftChild;
                else
                    parent2->rightChild=nullptr;
                curNode->rightChild=temp->rightChild;
                curNode->leftChild=temp->leftChild;
                root=curNode;
                delete temp;
            }
            n=this->root;
        }
        else{   //root��� �ƴҶ�
            if(curNode->rightChild==nullptr&&curNode->leftChild==nullptr){
                if(check==0){   //parent�� ���� �ڽ�
                    parent->rightChild=nullptr;
                }
                else{
                    parent->leftChild=nullptr;
                }
                delete curNode; curNode=nullptr;
            }
            else if(curNode->rightChild==nullptr||curNode->rightChild==nullptr){
                if(check==0)
                    parent->rightChild=curNode->rightChild;
                else
                    parent->leftChild=curNode->leftChild;
                delete curNode; curNode=nullptr;
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
                    curNode->rightChild=parent->rightChild->rightChild; 
                    curNode->leftChild=parent->rightChild->leftChild;
                    delete parent->rightChild;
                    parent->rightChild=curNode;
                }
                else{
                    curNode->rightChild=parent->leftChild->rightChild; 
                    curNode->leftChild=parent->leftChild->leftChild;
                    delete parent->leftChild;
                    parent->leftChild=curNode;
                }
            }
        }
        //�����ϴ� ���������� Ʈ�� ��ü�� ��鸮�Ƿ� ���������ʿ�
        //���������� �о ���ÿ� ����, �ϳ��� ����(���� ����� ������ ����)
        /*
        queue<Node *> q; stack<Node*> s;
        Node * searchNode=root;
        s.push(searchNode);
        while(searchNode){
            if(searchNode->leftChild!=nullptr){
                q.push(searchNode->leftChild);
            }
            if(searchNode->rightChild!=nullptr){
                q.push(searchNode->rightChild);
            }
            if(q.empty())   break;
            searchNode=q.front(); s.push(q.front()); q.pop(); 
        }
        while(s.empty()==false){
            s.top()=rotate(s.top()->calBF(),s.top());
            s.pop();
        }*/
        rotateAll(root);
    }
    else if(a>curNode->value){
        check=0;
        parent=curNode;
        del(a,curNode->rightChild);
    }
    else{
        check=1;
        parent=curNode;
        del(a,curNode->leftChild);
    }
    
}

void AVLtree::Showresult(Node * n){    //���� 7 levelOrder
    queue<Node*> q;
    Node * curNode=root;
    while(curNode){
        cout<<curNode->value;
        if(curNode->leftChild!=nullptr){
            cout<<"\tleft : "<<curNode->leftChild->value;
            q.push(curNode->leftChild);
        }
        else
            cout<<"\tleft : empty";
        if(curNode->rightChild!=nullptr){
            cout<<"\tright : "<<curNode->rightChild->value;
            q.push(curNode->rightChild);
        }
        else 
            cout<<"\tright : empty";
        cout<<endl;
        if(q.empty())   return;
        curNode=q.front(); q.pop(); 
    }
}

Node* AVLtree::rotate(int key, Node * parent){
    Node * Child;
    if(key<=1&&key>=-1) return parent;
    if(key>1){//LL�Ǵ� LRȸ��
        if(parent->leftChild->balFac==1){//LLȸ��
            Child=parent->leftChild;
            parent->leftChild=Child->rightChild;
            Child->rightChild=parent;
            return Child;
        }
        else{       //LRȸ��
            Node * grandChild;
            Child=parent->leftChild;
            grandChild=Child->rightChild;
            Child->rightChild=grandChild->leftChild;
            parent->leftChild=grandChild->rightChild;
            grandChild->leftChild=Child;
            grandChild->rightChild=parent;
            return grandChild;
        }
    }
    if(key<-1){//RR�Ǵ� RLȸ��
        if(parent->rightChild->balFac==-1){ //RRȸ��
            Child=parent->rightChild;
            parent->rightChild=Child->leftChild;
            Child->leftChild=parent;
            return Child;
        }
        else{       //RL ȸ��
            Node * grandChild;
            Child=parent->rightChild;
            grandChild=Child->leftChild;
            Child->leftChild=grandChild->rightChild;
            parent->rightChild=grandChild->leftChild;
            grandChild->rightChild=Child;
            grandChild->leftChild=parent;
            return grandChild;
        }
    } 
}
void AVLtree::rotateAll(Node *&n){
    if(n->rightChild!=nullptr)
        rotateAll(n->rightChild);
    if(n->leftChild!=nullptr)    
        rotateAll(n->leftChild);
    n=rotate(n->calBF(),n);
}