#ifndef SUBWAY_H
#define SUBWAY_H
#define INF 1000000000
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
ostream &operator<<(ostream &os, Vertex v);

class Vertex
{
private:
    int line;       //ȣ��
    string station; //���̸�
    int weight;   //����ġ
    int index;
public:
    Vertex()
    {
        line = NULL;
        station = "\0";
    };
    Vertex(int line, string station);
    int getLine() { return line; };
    string getStation() { return station; };
    bool operator==(Vertex ver2)
    {
        if (this->line == ver2.line && this->station == ver2.station) //ȣ����, ���� ������
            return true;
        else
            return false;
    };
    void setWeight(Vertex &v);
    void setIndex(int index){ this->index = index; };
    int getIndex(){ return this->index; };
    int getWeight(){ return this->weight; };
};

class Graph
{
private:
    vector<int> dist; //�Ÿ� �迭
    vector<bool> check;
    vector<Vertex> *HeadNodes;
    vector<Vertex> vertex; //��� ������ ����
public:
    int choose(const int n);
    Graph(int numLine, istream &f);
    void findShortestWay(Vertex from, Vertex to);             //A���� B�ΰ��� �ִܰŸ�
    string findFairPoint(Vertex terminal1, Vertex terminal2); //A�� B �߰��� ����
    int findIndex(Vertex station);         //graph���� ����� �ε��� ã���ִ� �Լ�
    bool isVertexExist(Vertex station);    //���� �̹� �Էµ����� �ִ��� ã���ִ� �Լ�
};
#endif