#include <iostream>
//삽입정렬, n개의 원소가 있다고치면, 1부터 n까지 인덱스 사용
template<class T>
void Insert(const T& e, T*a, int i){
    a[0]=e;
    while(e<a[i]){
        a[i+1]=a[i];
        i--;
    }
    a[i+1]=e;
}
template<class T>
void InsertionSort(T*a, const int n){
    for(int j=2; j<=n;j++){
        T temp=a[j];
        Insert(temp,a,j-1);
    }
}