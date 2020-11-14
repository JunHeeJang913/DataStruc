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
class Vertex{
private:
    int line;       //ȣ��
    string station; //���̸�
public:
    Vertex(int line , string station);
    int getLine();      
    string getStation();
};
ostream& operator <<(ostream& os, Vertex v);
class Edge{
private:
    Vertex from, to;
    int weight;
};
class Graph{
private:
    vector<Vertex> *graph;
    Vertex * vertex;    //��� ������ ����
    Edge * edge;        //��� ������ ����
public:
    Graph();
    void findShortestWay(Vertex form, Vertex to);       //A���� B�ΰ��� �ִܰŸ�
    string findFairPoint(Vertex terminal1, Vertex terminal2);     //A�� B �߰��� ����
    void initialize();
};
#endif