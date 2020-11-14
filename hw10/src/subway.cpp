#include "subway.h"
using namespace std;
ostream& operator <<(ostream& os, Vertex v){
    os<<v.getStation()<<endl;
}
Vertex::Vertex(int line , string station){
    this->line = line;
    this->station=station;
}

Edge::Edge(Vertex& from, Vertex& to, int weight){
    this->from = from;
    this->to = to;
    this->weight = weight;
}
Graph::Graph(istream& f){
    int n;  
    f>>n;      //���� �ִ� ����
    edge=new Edge[n];   
    n=n*2;   //���� �ִ� ����(�����̸� ���� 4��)
    vertex=new Vertex[n];
    graph = new vector<Vertex>[n];
    
}
