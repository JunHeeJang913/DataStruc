#include <iostream>
#include "GenList.h"
using namespace std;

void GenList::Make(GenListNode *&cur)
{
    char i;
    cin >> i;
    if (i == ')')
        return;
    else if (i == '(')          
    {
        cur = new GenListNode();
        cur->tag=true;
        Make(cur->down);
        Make(cur->next);
    }
    else
    {
        cur = new GenListNode();
        cur->tag=false; cur->data=i;
        Make(cur->next);
    }
}

void GenList::Print(GenListNode *&cur)
{
    if(cur->tag==false){
        cout<<cur->data;
        if(cur->next!=NULL)
            Print(cur->next);
        else{
            cout<<')';
            return;
        }
    } 
    else if(cur->tag == true){
        cout<<'(';
        if(cur->down!=NULL)
            Print(cur->down);
        else
            cout<<')';        
        if(cur->next!=NULL)        
            Print(cur->next);
        else{
            cout<<')';
            return;
        }
    }
}

void GenList::Insert(GenListNode *&cur, char i, char j)
{
    if((cur->tag==0)){
        if(cur->data==i){
            GenListNode * newNode;
            newNode=new GenListNode();
            newNode->next=cur->next;
            cur->next=newNode;
            newNode->data=j;
            newNode->tag=0;
        }
        if(cur->next!=NULL)
            Insert(cur->next,i,j);
    }
    else if((cur->tag==1)){
        if(cur->down!=NULL)
            Insert(cur->down,i,j);
        if(cur->next!=NULL)
            Insert(cur->next,i,j);
    }
    if(cur->next==NULL){
        return;
    }
}

void GenList ::Delete(GenListNode *&cur, char i)
{    
    if(cur->tag==0){    
        if(cur->data==i){
            if(cur->next!=NULL){
                cur=cur->next;
                Delete(cur,i);
            }
            else{       
                cur=NULL;
                return;
            }
        }
        else{
            if(cur->next!=NULL){
                Delete(cur->next,i);
            }
            else{       
                return;
            }
        }
    }
    else{   //tag=1
        if(cur->down!=NULL){
            if(cur->down->data==i){
                if(cur->down->next!=NULL){
                    cur->down=cur->down->next;
                    Delete(cur->down,i);
                    if(cur->next!=NULL){
                        Delete(cur->next,i);
                    }
                    else
                        return; 
                }
                else{
                    cur->down=NULL;
                    if(cur->next!=NULL){
                        Delete(cur->next,i);
                    }
                    else
                        return;
                }   
            }
            else{
                Delete(cur->down,i);
                if(cur->next!=NULL){
                    Delete(cur->next,i);
                }
                else
                    return; 
            }         
        }
        else{
            if(cur->next!=NULL){
                Delete(cur->next,i);
            }
            else
                return;     
        }
    }
}