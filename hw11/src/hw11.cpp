#include <fstream>
#include <iostream>
using namespace std;
//input data=>정수, 1~100000
template <class T>
void PrintArray(T *a, const int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
//adjust, heapsort구현
template <class T>
void adjust(T*a,const int root, const int n){
    T e = a[root];
    int j;
    for(j=2*root;j<=n;j=j*2){
        if(j<n&&a[j]<a[j+1])
            j++;
        if(e>=a[j])
            break;
        a[j/2]=a[j];
    }
    a[j/2]=e;
}
template <class T>
void HeapSort(T*a, const int n){
    for(int i=n/2;i>=1;i--){    
    //초기에 입력받은 인덱스들을 맥스힙으로 정렬해준다.
        adjust(a,i,n);
    }
    PrintArray(a,n);
    for(int i=n-1;i>=1;i--){        //한칸씩 줄여가며 정렬한다.
        swap(a[1],a[i+1]);         //현 히프의 처음과 마지막을 교환
        adjust(a,1,i);      //교환하면서, 망가진 힙구조를 되돌린다.
        PrintArray(a,i);
    }
}
int main(int argc, char *argv[])
{
    // 구현 score에서 데이터 받아오기
    int * a;
    int n;
    fstream fin(argv[1]);
    int numberOfNodes;
    fin>>numberOfNodes;
    a = new int[numberOfNodes+1];
    n=numberOfNodes;
    for(int i=1;i<numberOfNodes+1;i++){
        int temp;
        fin>>temp;
        a[i]=temp;
    }
    cout << "Before Sorting : ";
    //a는 T형 배열을 가리키는 포인터.
    //n은 배열 원소의 개수(파일의 가장 첫줄)
    PrintArray(a, n);      
    HeapSort(a, n);
    cout << "After Sorting : ";
    PrintArray(a, n);
}