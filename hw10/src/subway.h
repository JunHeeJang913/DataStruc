#ifndef SUBWAY_H
#define SUBWAY_H
#define INF 2147483647
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Vertex
{
private:
    int line;       //호선
    string station; //역이름
    int dist;   //가중치
    int index;
public:
    Vertex()
    {
        line = 0;
        station = "\0";
    };
    Vertex(int line, string station);
    int getLine() { return line; };
    string getStation() { return station; };
    bool operator==(Vertex ver2)        //비교연산자
    {
        if (this->line == ver2.line && this->station == ver2.station) //호선도, 역도 같으면
            return true;
        else
            return false;
    };
    void setDist(Vertex &v);
    void setIndex(int index){ this->index = index; };
    int getIndex(){ return this->index; };
    int getDist(){ return this->dist; };
};

class Graph
{
private:
    int numOfVertex;
    vector<int> dist; //거리 배열
    vector<vector<Vertex> > HeadNodes;
    vector<Vertex> vertex; //모든 정점의 집합
    vector<int> route;
public:
    Graph(int numLine, istream &f);
    void findShortestWay(int fromIndex, int toIndex);             //A부터 B로가는 최단거리
    void findFairPoint(int terminal1, int terminal2); //A와 B 중간의 지점
    int findIndex(Vertex station);         //graph에서 사용할 인덱스 찾아주는 함수
    bool isVertexExist(Vertex station);    //역이 이미 입력된적이 있는지 찾아주는 함수
    void printShortestWay(int fromIndex, int toIndex);
};
//findShortestway, printshortestway, findfairpoint 모두 인덱스를 인자로 받게하고, 인덱스는 메인함수에서 한번만 구하는걸로..
#endif