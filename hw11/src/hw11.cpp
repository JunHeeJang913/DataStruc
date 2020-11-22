#include <fstream>
#include <iostream>
using namespace std;
//input data=>����, 1~100000
template <class T>
void PrintArray(T *a, const int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
//adjust, heapsort����
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
    //�ʱ⿡ �Է¹��� �ε������� �ƽ������� �������ش�.
        adjust(a,i,n);
    }
    PrintArray(a,n);
    for(int i=n-1;i>=1;i--){        //��ĭ�� �ٿ����� �����Ѵ�.
        swap(a[1],a[i+1]);         //�� ������ ó���� �������� ��ȯ
        adjust(a,1,i);      //��ȯ�ϸ鼭, ������ �������� �ǵ�����.
        PrintArray(a,i);
    }
}
int main(int argc, char *argv[])
{
    // ���� score���� ������ �޾ƿ���
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
    //a�� T�� �迭�� ����Ű�� ������.
    //n�� �迭 ������ ����(������ ���� ù��)
    PrintArray(a, n);      
    HeapSort(a, n);
    cout << "After Sorting : ";
    PrintArray(a, n);
}