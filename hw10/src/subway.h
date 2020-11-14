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
    int line;       //호선
    string station; //역이름
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
    Vertex * vertex;    //모든 정점의 집합
    Edge * edge;        //모든 간선의 집합
public:
    Graph(istream& );
    void findShortestWay(Vertex form, Vertex to);       //A부터 B로가는 최단거리
    string findFairPoint(Vertex terminal1, Vertex terminal2);     //A와 B 중간의 지점
};
#endif