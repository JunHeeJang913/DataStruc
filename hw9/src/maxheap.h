#ifndef __MAXHEAP_H__
#define __MAXHEAP_H__
#include <iostream>
#include <algorithm>
using namespace std;
template <class T>
class Maxheap
{
private:
    void ChangeSize1D(int);
    T *heap;
    int heapSize;
    int capacity;

public:
    Maxheap(int);
    void Push(const T &);
    void Pop();
    bool IsEmpty() { return heapSize == 0; }
    T Top() { return heap[1]; }
    template <class T2>
    friend ostream &operator<<(ostream &, Maxheap<T2> &);
};
template <class T>
void Maxheap<T>::ChangeSize1D(int size)
{ //heap의 크기를 size만큼 늘리는 함수.
    if(size<=0)throw"추가하고자하는 크기는 양수여야합니다";
    T*temp = new T[size+capacity+1];      //늘리고자하는 size, 노드저장가능개수, [0]
    int number=size;
    copy(heap,heap+capacity+1,temp);
    delete [] heap;
    heap=temp;
}
template <class T>
void Maxheap<T>::Push(const T &newdata)
{
    if(heapSize==capacity){
        ChangeSize1D(capacity+1);
        capacity*=2;
    }
    int currentNode=++heapSize;
    while(currentNode!=1&&heap[currentNode/2]<newdata){ //bubble up
        heap[currentNode]=heap[currentNode/2];  //move parent down
        currentNode /=2;
    }
    heap[currentNode]=newdata;
}
template <class T>
void Maxheap<T>::Pop()
{//delete max element
    if(IsEmpty()) throw "heap is empty. Cannot Delete";
    heap[1].~T();//delete max element
    T lastE = heap[heapSize--]; //remove last element from heap

    //trickle down
    int currentNode=1;  //root
    int child=2;    //a child of currentNode
    while(child<=heapSize){ //아들이 있는 경우     
        //set child to larger child of currentNode
        if(child<heapSize&&heap[child]<heap[child+1])child++;
        if(lastE>=heap[child])break;//can we put lastE in currentNode?

        heap[currentNode]=heap[child];  //move child up
        currentNode=child;child*=2;     //move down a level
    }
    heap[currentNode]=lastE;
}
template <class T>
ostream &operator<<(ostream &os, Maxheap<T> &H)
{
    os << "<Heap contents> ";
    int i;
    for (i = 1; i <= H.heapSize; i++)
        os << i << ":" << H.heap[i] << " ";
    os << endl;
}
template <class T>
Maxheap<T>::Maxheap(int _capacity = 10) : heapSize(0)
{
    if (_capacity < 1)
        throw " Must be > 0";
    capacity = _capacity;
    heap = new T[capacity + 1];     //[0]을 비워두기 때문!!
}
#endif