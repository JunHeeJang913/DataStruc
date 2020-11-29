#include <iostream>
#include <fstream>
#include <ctime>
#include "sort.h"
using namespace std;
int main(int argc, char *argv[])
{
    int T = atoi(argv[1]); // num of test case
    cout << "T=" << T << endl;
    int N;             // 각 테스트케이스 별 레코드의 길이
    int i;             // iterator
    clock_t result[6]; // result 배열에 각 알고리즘 별로 실행시간을 저장하게 됩니다.
    // result[0]: insertion sort
    // result[1]: quick sort
    // result[2]: iterative merge sort
    // result[3]: reculsive merge sort
    // result[4]: natural merege sort
    // result[5]: heap sort
    clock_t start;
    clock_t end;
    if (argc < 3)
    {
        cerr << "wrong argument count" << endl;
        return 1;
    }
    cout << "--INS--|-QUICK-|-MERGE-|-RECMG-|-NATMG-|-HEAP--| " << endl;
    for (i = 2; i < T + 2; i++)
    {
        // i번째 인자의 파일을 읽습니다.
        // 각 정렬 알고리즘에 필요한 자료구조를 생성하고 데이터를 담습니다.
        // 여기부터 정렬 시간 측정을 시작합니다.
        /* example
        start = clock();
        삽입정렬 수행
        end = clock();
        result[0] = end-start; */
        // 결과를 출력합니다. (이 부분은 수정하지 않습니다)
        cout.precision(5);
        cout << fixed;
        for (int j = 0; j < 6; j++)
        {
            cout << (double)result[j] / CLOCKS_PER_SEC << "|";
        }
        cout << "N=" << N << endl;
    }
}