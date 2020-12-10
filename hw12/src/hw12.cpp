#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
#include "sort.h"
using namespace std;
struct timeval start_t, end_t;
int main(int argc, char *argv[])
{
    int T = atoi(argv[1]); // num of test case
    cout << "T=" << T << endl;
    int N;             // �� �׽�Ʈ���̽� �� ���ڵ��� ����
    int i;             // iterator
    double result[6]; // result �迭�� �� �˰��� ���� ����ð��� �����ϰ� �˴ϴ�.
    double diff_t;
    // result[0]: insertion sort
    // result[1]: quick sort
    // result[2]: iterative merge sort
    // result[3]: reculsive merge sort
    // result[4]: natural merege sort
    // result[5]: heap sort
    
    if (argc < 3)
    {
        cerr << "wrong argument count" << endl;
        return 1;
    }
    cout << "--INS--|-QUICK-|-MERGE-|-RECMG-|-NATMG-|-HEAP--| " << endl;
    for (i = 2; i < T + 2; i++)
    {
        fstream fin(argv[i]);
        fin>>N;
        int * ins= new int [N+1];
        int * quick=new int [N+1];
        int * merge=new int [N+1];
        int * recmg=new int [N+1];
        int * natmg=new int [N+1];
        int * heap=new int [N+1];
        for(int j=1;j<=N;++j){
            fin>>ins[j];
            quick[j]=ins[j];
            merge[j]=ins[j];
            recmg[j]=ins[j];
            natmg[j]=ins[j];
            heap[j]=ins[j];
        }
        fin.close();
        // i��° ������ ������ �н��ϴ�.
        // �� ���� �˰��� �ʿ��� �ڷᱸ���� �����ϰ� �����͸� ����ϴ�.
        // ������� ���� �ð� ������ �����մϴ�.
        
        gettimeofday(&start_t, NULL); 
        //�������� ���� ...
        InsertionSort(ins,N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[0] = diff_t;

        gettimeofday(&start_t, NULL); 
        //������ ���� ...
        QuickSort(quick, 1, N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[1] = diff_t;

        gettimeofday(&start_t, NULL); 
        //�պ����� ���� ...
        MergeSort(merge, N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[2] = diff_t;

        int * link = new int [N+1];
        for(int i=0;i<N+1;i++){
            link[i]=0;
        }
        gettimeofday(&start_t, NULL); 
        //��ȯ�պ����� ���� ...
        rMergeSort(recmg,link, 1,N);
        gettimeofday(&end_t, NULL); 

        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[3] = diff_t;

        gettimeofday(&start_t, NULL); 
        //�ڿ��պ����� ���� ...
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[4] = diff_t;

        gettimeofday(&start_t, NULL); 
        //������ ���� ...
        HeapSort(heap, N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[5] = diff_t;
        
        // ����� ����մϴ�. (�� �κ��� �������� �ʽ��ϴ�)
        
        cout.precision(5);
        cout << fixed;
        for (int j = 0; j < 6; j++)
        {
            cout << (double)result[j] / CLOCKS_PER_SEC << "|";
        }
        cout << "N=" << N << endl;

        //�Ҵ�����
        delete [] ins;
        delete [] quick;
        delete [] merge;
        delete [] recmg;
        delete [] natmg;
        delete [] heap;
    }
}