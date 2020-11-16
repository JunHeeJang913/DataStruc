#include "subway.h"
using namespace std;
//============================================================================
ostream& operator <<(ostream& os, Vertex& v){
    os<<v.getStation()<<endl;
}
//============================================================================
Vertex::Vertex(int line, string station){
    this->line = line;
    this->station=station;
}
//============================================================================
int Graph::findIndex(Vertex station){
        int index=0;
        for(Vertex x:vertex){
            if(x==station){
                return index;
            }
            index++;
        }
}
//============================================================================
bool Graph::isVertexExist(Vertex station){
    for(Vertex x:vertex){
        if(x==station){     //���� �����Ѵٸ� ���� ��ȯ
            return true;
        }
    }
    return false;   //�� ���ƺôµ� ������ ������ ��ȯ
}
//============================================================================
void Vertex::setWeight(Vertex& v){
    if(this->line!=v.line&&this->station==v.station)
        this->weight=1;
    else if(this->line==v.line&&this->station==v.station)
        this->weight=2;
}
//============================================================================
Graph::Graph(int numLine, istream& f){
    int line1,line2;
    string stat1,stat2;
    int n = 2*numLine;  //���� �ִ� ������ numline*2;
    int index=0;
    HeadNodes = new vector<Vertex>[n];
    while(f){       //�׷��� ����� ����
        f>>line1; f>>stat1; f>>line2; f>>stat2;
        Vertex temp1(line1,stat1); Vertex temp2(line2,stat2);
        /*
        ���ο� �����̶��, �߰�
        ������ ����⿡ ����(��ΰ� ���ο� �����̹Ƿ� �׳� ������ ��)
        ���� ��������Ʈ ������ �׷��� �����
        ex)���̸��� �ԷµǸ�, vertex���� ���Ҹ� ã�Ƽ� �� �ε���(i)�� ��ȯ�ϰ�
            �� �ε����� ��ġ�� HeadNodes[i]���� ã���� �ȴ�.
        */
       temp2.setWeight(temp1);  temp1.setWeight(temp2); //���̵� ����
       //���� temp1, temp2�� �� �����̶�� ���� ���տ� �߰�.
       if(isVertexExist(temp1)==false){
           temp1.setIndex(index);
           vertex[index]=temp1;
           index++;
       }
       else{    //���� ��(ȣ��, �� �̸�)�� �ִٸ�, ���� �������� ����� ���� �ε������� �����´�. 
           temp1.setIndex(findIndex(temp1));
       }
       if(isVertexExist(temp2)==false){
           temp2.setIndex(index);
           vertex[index]=temp1;
           index++;
       }
       else{    //���� ��(ȣ��, �� �̸�)�� �ִٸ�, ���� �������� ����� ���� �ε������� �����´�.
           temp2.setIndex(findIndex(temp2));
       }
       //������ ��� �����ϴ� �����鿡 ���ؼ�
       HeadNodes[temp1.getIndex()].push_back(temp2);
       HeadNodes[temp2.getIndex()].push_back(temp1);    //������̹Ƿ�
       //temp1�� ���ؼ�
       /*if(isVertexExist(temp1)==true){
           HeadNodes[findIndex(temp1)].push_back(temp2);
       }
       else{        //���ο� ����
            vertex.push_back(temp1);
            HeadNodes[findIndex(temp1)].push_back(temp2);
       }
       //temp2�� ���ؼ�
       if(isVertexExist(temp2)==true){
           HeadNodes[findIndex(temp2)].push_back(temp1);
       }
       else{        //���ο� ����
            vertex.push_back(temp2);
            HeadNodes[findIndex(temp2)].push_back(temp1);
       }*/
    }
    for(int i=0;i<index+1;i++){
        dist[i]=INF;
    }//�ϴ� ���Ѵ�� ä���.    
    //�뼱�� �ϼ�!
}
//============================================================================
int Graph::choose(const int n){
    // choose returns a value u such that
    //dist[u]=minimum dist[w], where check[w]=False
    int min=INF;
    int a;
    vector<int>::iterator itr=dist.begin();
    for(int i=0; itr!=dist.end(); itr+i){
        if(*itr<min&&check[i]==false){
            min=*itr;
            a=i;
        }
    }
    return a;
}
//============================================================================
void Graph::findShortestWay(Vertex from, Vertex to){       //���ͽ�Ʈ�� �˰���,���Ḯ��Ʈ,�켱���� ť�� �̿�
    int fromIndex, toIndex;
    fromIndex=findIndex(from);
    toIndex=findIndex(to);
    dist[fromIndex]=0;
    priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > pq; 
    //�켱���� ť�� pair�� ��� first�� �������� ����, <����ġ, �ε���> ���̴�.
    //�켱����ť<�ڷ���,����ü(��� vector<�ڷ���>),�񱳿�����(�⺻���� less<�ڷ���>)
    //greater�� �ϸ� ������������ ����, �⺻������ �ϸ� ��������
    pq.push(make_pair(0,fromIndex));
    while(!pq.empty()){
        int distance = pq.top().first;
        int current = pq.top().second;
        pq.pop();
        if(dist[current]<distance) continue;
        for(int i=0;i<HeadNodes[current].size();i++){
            int nextDist = distance+HeadNodes[current][i].getWeight();
            int next = HeadNodes[current][i].getIndex();
            if(nextDist < dist[next]){  //�� �������ٸ�
                dist[next] = nextDist;
                pq.push(make_pair(nextDist, next));
            }
        }
    }
    
}
//============================================================================
string Graph::findFairPoint(Vertex terminal1, Vertex terminal2){

}    
//============================================================================
