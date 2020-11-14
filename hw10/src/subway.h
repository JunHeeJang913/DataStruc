#ifndef SUBWAY_H
#define SUBWAY_H
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
ostream& operator <<(ostream& os, Vertex v);
class Vertex{
private:
    int line;       //ȣ��
    string station; //���̸�
public:
    Vertex(){line=NULL;station="\0";};
    Vertex(int line, string station);
    int getLine() { return line; };
    string getStation() { return station; };
};

class Edge{
private:
    Vertex from, to;
    int weight;
public:
    Edge();
    Edge(Vertex& from, Vertex& to, int weight);
};
class Graph{
private:
    vector<Vertex> * graph;
    Vertex * vertex;    //��� ������ ����
    Edge * edge;        //��� ������ ����
public:
    Graph(istream& );
    void findShortestWay(Vertex form, Vertex to);       //A���� B�ΰ��� �ִܰŸ�
    string findFairPoint(Vertex terminal1, Vertex terminal2);     //A�� B �߰��� ����
};
#endif