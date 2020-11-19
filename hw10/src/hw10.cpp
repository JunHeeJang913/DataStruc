#include "subway.h"
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
    int numLine;
    int line1, line2;
    string src, dst;
    if (argc != 3)
    {
        cerr << "Argument Count is " << argc << endl
             <<"Argument must be " << argc << endl;
        return 1;
    }

    fstream fin(argv[1]);
    if (!fin)
    {
        cerr << argv[1] << " open failed" << endl;
        return 1;
    }
    fin >> numLine;
    //데이터 입력받아 지하철노선도 만들기
    Graph subwayMap(numLine, fin);      //subwayMap객체 생성
    fin.close();
    fstream fin2(argv[2]);
    if (!fin2)
    {
        cerr << argv[2] << " open failed" << endl;
        return 1;
    }
    fin2 >> line1 >> src;
    fin2 >> line2 >> dst;
    fin2.close();
    Vertex from(line1, src);
    Vertex to(line2, dst);
    int fromIndex = subwayMap.findIndex(from); 
    int toIndex = subwayMap.findIndex(to);
    subwayMap.findShortestWay(fromIndex, toIndex);
    subwayMap.printShortestWay(fromIndex,toIndex);
    subwayMap.findFairPoint(fromIndex,toIndex);
    //결과 출력
    return 0;
}