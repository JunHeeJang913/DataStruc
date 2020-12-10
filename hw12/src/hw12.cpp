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
    int N;             // 각 테스트케이스 별 레코드의 길이
    int i;             // iterator
    double result[6]; // result 배열에 각 알고리즘 별로 실행시간을 저장하게 됩니다.
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
        // i번째 인자의 파일을 읽습니다.
        // 각 정렬 알고리즘에 필요한 자료구조를 생성하고 데이터를 담습니다.
        // 여기부터 정렬 시간 측정을 시작합니다.
        
        gettimeofday(&start_t, NULL); 
        //삽입정렬 수행 ...
        InsertionSort(ins,N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[0] = diff_t;

        gettimeofday(&start_t, NULL); 
        //퀵정렬 수행 ...
        QuickSort(quick, 1, N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[1] = diff_t;

        gettimeofday(&start_t, NULL); 
        //합병정렬 수행 ...
        MergeSort(merge, N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[2] = diff_t;

        int * link = new int [N+1];
        for(int i=0;i<N+1;i++){
            link[i]=0;
        }
        gettimeofday(&start_t, NULL); 
        //순환합병정렬 수행 ...
        rMergeSort(recmg,link, 1,N);
        gettimeofday(&end_t, NULL); 

        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[3] = diff_t;

        gettimeofday(&start_t, NULL); 
        //자연합병정렬 수행 ...
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[4] = diff_t;

        gettimeofday(&start_t, NULL); 
        //힙정렬 수행 ...
        HeapSort(heap, N);
        gettimeofday(&end_t, NULL); 
        diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000); 
        result[5] = diff_t;
        
        // 결과를 출력합니다. (이 부분은 수정하지 않습니다)
        
        cout.precision(5);
        cout << fixed;
        for (int j = 0; j < 6; j++)
        {
            cout << (double)result[j] / CLOCKS_PER_SEC << "|";
        }
        cout << "N=" << N << endl;

        //할당해제
        delete [] ins;
        delete [] quick;
        delete [] merge;
        delete [] recmg;
        delete [] natmg;
        delete [] heap;
    }
}