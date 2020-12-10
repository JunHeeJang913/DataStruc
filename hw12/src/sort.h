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
//��������, n���� ���Ұ� �ִٰ�ġ��, 1���� n���� �ε��� ���
template<class T>
void Insert(const T& e, T*a, int i){
    //���� ���� ���� ���� �迭 ��ҿ� ���� ���ذ���,
    //������ ��ġ�� ����
    a[0]=e;
    while(e<a[i]){
        a[i+1]=a[i];
        i--;
    }
    a[i+1]=e;
}
template<class T>
void InsertionSort(T*a, const int n){
    //Insert�Լ��� �ݺ������� �ҷ�����
    //�迭�� ������
    for(int j=2; j<=n;j++){
        T temp=a[j];
        Insert(temp,a,j-1);
    }
}
//������
template <class T>
void QuickSort(T *a, const int left, const int right){
    //������ ���ڵ� �� �ǹ�(����) ���ڵ� ����
    //������ ���ڵ���� �ٽ� ����
    //�� ������ recursive�ϰ� ���
    if(left<right){
        int i=left,j=right+1,pivot=a[left];
        do{
            do i++; while(a[i]<pivot);
            do j--; while(a[j]>pivot);
            if(i<j) swap(a[i],a[j]);
        }while(i<j);//�ǹ� ����(i==j, i>j)��, ������ ���ڵ� ������.
        swap(a[left],a[j]);//�ǹ��� �߰�����

        QuickSort(a,left,j-1);  //�ǹ����� ���� �迭 ����
        QuickSort(a,j+1, right);    //�ǹ����� ���� �迭 ����
    }
}
//�պ�����-�ݺ��պ�����(Iterative Merge Sort)
template<class T>
void Merge(T*initList, T*mergedList, const int l, const int m, const int n){
    //�ΰ��� ���ĵ� ����Ʈ(initList[l:m],initList[m+1:n])�� �ϳ��� ���ĵ� ����Ʈ(mergedList)�� �պ�
    int i1, iResult, i2;
    for(i1=l, iResult=l, i2=m+1;i1<=m&&i2<=n;iResult++){
        //1->���ĸ���Ʈ1, 2->���ĸ���Ʈ2
        if(initList[i1]<=initList[i2]){
            mergedList[iResult]=initList[i1];
            i1++;
        }
        else{
            mergedList[iResult]=initList[i2];
            i2++;
        }
    }
    //�� �������� �� ����Ʈ�� ���� ���ҵ��� �ִٸ�, �������ش�.
    copy(initList+i1,initList+m+1, mergedList+iResult);
    copy(initList+i2,initList+n+1, mergedList+iResult);
}
template <class T>
void MergePass(T *initList,T*resultList, const int n , const int s){
    //�պ������� �������� �պ��ܰ�(pass)�� ���еȴ�.
    //initList�� s�� �� �ΰ��� �ɰ��� �迭�̴�. resultList�� 2*s ������ ���ĵ�.
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

//�պ�����-��ȯ
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
    //recursive�ϰ�, ���� ���� �� ����Ʈ
    if(left>=right) return left;
    int mid=(left+right)/2;
    return rMerge(a, link,
                     rMergeSort(a, link, left, mid),
                     rMergeSort(a, link, mid+1,right));
}



//�պ�����-�ڿ�



//������
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