#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <algorithm>
using namespace std;
template <class T>
void printArray(T*a, const int n){
    for(int i=1;i<=n;++i){
        cout<<a[i]<<" ";
        if(i%10==0)
            cout<<endl;
    }
    cout<<endl;
}
template<class T>
void printArray(T*a, int *link, const int n){
    int count=1;
    int min=a[1]; int minIndex=1;
    for(int i=1;i<n+1;i++){
        if(min>a[i]){
            min=a[i]; minIndex=i;
        }
    }
    for(int i=minIndex;i!=0;count++){
        cout<<a[i]<<" ";
        if(count%10==0)
            cout<<endl;
        i=link[i];
    }
    cout<<endl;
}
//삽입정렬, n개의 원소가 있다고치면, 1부터 n까지 인덱스 사용
template<class T>
void Insert(const T& e, T*a, int i){
    //새로 들어온 값을 기존 배열 요소와 각각 비교해가며,
    //적당한 위치에 삽입
    a[0]=e;
    while(e<a[i]){
        a[i+1]=a[i];
        i--;
    }
    a[i+1]=e;
}
template<class T>
void InsertionSort(T*a, const int n){
    //Insert함수를 반복적으로 불러내서
    //배열을 정렬함
    for(int j=2; j<=n;j++){
        T temp=a[j];
        Insert(temp,a,j-1);
    }
}
//퀵정렬
template <class T>
void QuickSort(T *a, const int left, const int right){
    //정렬할 레코드 중 피벗(중추) 레코드 선택
    //정렬할 레코드들을 다시 정돈
    //퀵 정렬을 recursive하게 사용
    if(left<right){
        int i=left,j=right+1,pivot=a[left];
        do{
            do i++; while(a[i]<pivot);
            do j--; while(a[j]>pivot);
            if(i<j) swap(a[i],a[j]);
        }while(i<j);//피벗 선택(i==j, i>j)과, 정렬할 래코드 재정돈.
        swap(a[left],a[j]);//피벗이 중간점에

        QuickSort(a,left,j-1);  //피벗기준 좌측 배열 정렬
        QuickSort(a,j+1, right);    //피벗기준 우측 배열 정렬
    }
}
//합병정렬-반복합병정렬(Iterative Merge Sort)
template<class T>
void Merge(T*initList, T*mergedList, const int l, const int m, const int n){
    //두개의 정렬된 리스트(initList[l:m],initList[m+1:n])를 하나의 정렬된 리스트(mergedList)로 합병
    int i1, iResult, i2;
    for(i1=l, iResult=l, i2=m+1;i1<=m&&i2<=n;iResult++){
        //1->정렬리스트1, 2->정렬리스트2
        if(initList[i1]<=initList[i2]){
            mergedList[iResult]=initList[i1];
            i1++;
        }
        else{
            mergedList[iResult]=initList[i2];
            i2++;
        }
    }
    //위 과정에서 각 리스트에 남은 원소들이 있다면, 복사해준다.
    copy(initList+i1,initList+m+1, mergedList+iResult);
    copy(initList+i2,initList+n+1, mergedList+iResult);
}
template <class T>
void MergePass(T *initList,T*resultList, const int n , const int s){
    //합병정렬은 여러개의 합병단계(pass)로 구분된다.
    //initList가 s개 씩 두개로 쪼개진 배열이다. resultList는 2*s 단위로 정렬됨.
    int i;
    for(i=1; i<=n-2*s+1;i+=2*s)
        Merge(initList, resultList, i,i+s-1, i+2*s-1);
    if((i+s-1)<n)
        Merge(initList,resultList,i,i+s-1,n);
    else
        copy(initList+i,initList+n+1,resultList+i);
}
template<class T>
void MergeSort(T*a, const int n){
    T * tempList = new T[n+1];
    for(int l=1; l<n;l*=2){
        MergePass(a, tempList, n, l);
        l *=2;
        MergePass(tempList,a,n,l);
    }
    delete [] tempList;
}

//합병정렬-순환
template<class T>
int rMerge(T*a, T*link, const int start1, const int start2){
    int iResult=0;
    int i1=start1; int i2=start2;
    for(;i1&&i2;){
        if(a[i1]<=a[i2]){
            link[iResult]=i1;
            iResult=i1; i1=link[i1];
        }
        else{
            link[iResult]=i2;
            iResult=i2; i2=link[i2];
        }
    }
    if(i1==0) link[iResult]=i2;
    else link[iResult]=i1;
    return link[0];
}

template <class T>
int rMergeSort(T*a, T* link, const int left, const int right){
    //recursive하게, 거의 같은 두 리스트
    if(left>=right) return left;
    int mid=(left+right)/2;
    return rMerge(a, link,
                     rMergeSort(a, link, left, mid),
                     rMergeSort(a, link, mid+1,right));
}



//합병정렬-자연



//힙정렬
template <class T>
void Adjust(T*a, const int root, const int n){
    T e=a[root];
    int j;
    for(j=2*root; j<=n; j*=2){
        if(j<n&&a[j]<a[j+1]) j++;
        if(e>=a[j]) break;
        a[j/2]=a[j];
    }
    a[j/2]=e;
}

template <class T>
void HeapSort(T*a, const int n){
    for(int i=n/2;i>=1;i--)
        Adjust(a,i,n);
    for(int i=n-1;i>=1;i--){
        swap(a[1],a[i+1]);
        Adjust(a,1,i);
    }
}
//


#endif