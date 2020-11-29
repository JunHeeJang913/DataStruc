#include "subway.h"
using namespace std;
//============================================================================
ostream& operator <<(ostream& os, Vertex& v){
    os<<v.getStation();
    return os;
}
//============================================================================
Vertex::Vertex(int line, string station){
    this->line=line;
    this->station=station;
}
//============================================================================
int Graph::findIndex(Vertex station){      
        int index=0;
        vector<Vertex>::iterator itr=vertex.begin(); 
        for(; itr!=vertex.end();++itr){
            if(*itr==station){
                return itr-vertex.begin();
            }
        }  
}
//============================================================================
bool Graph::isVertexExist(Vertex station){
    vector<Vertex>::iterator itr=vertex.begin();
    for (; itr!=vertex.end(); ++itr){
        if (*itr==station){
            return true;
        }
    }
    return false;
    /*for(Vertex x:vertex){
        if(x==station){     //���� �����Ѵٸ� ���� ��ȯ
            return true;
        }
    }
    return false;   //�� ���ƺôµ� ������ ������ ��ȯ
*/
}
//============================================================================
void Vertex::setDist(Vertex& v){
    if(this->line!=v.line&&this->station==v.station)
        this->dist=1;
    else if(this->line==v.line&&this->station!=v.station)
        this->dist=2;
}
//============================================================================
Graph::Graph(int numLine, istream& f){
    int line1,line2;
    string stat1,stat2;
    int index=0;
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
       temp2.setDist(temp1);  temp1.setDist(temp2); //���̵� ����
       //���� temp1, temp2�� �� �����̶�� ���� ���տ� �߰�.
       if(isVertexExist(temp1)==false){
           HeadNodes.resize(index+1);
           temp1.setIndex(index);
           vertex.push_back(temp1);
           index++;
       }
       else{    //���� ��(ȣ��, �� �̸�)�� �ִٸ�, ���� �������� ����� ���� �ε������� �����´�. 
           temp1.setIndex(findIndex(temp1));
       }
       if(isVertexExist(temp2)==false){
           HeadNodes.resize(index+1);
           temp2.setIndex(index);
           vertex.push_back(temp2);
           index++;
       }
       else{    //���� ��(ȣ��, �� �̸�)�� �ִٸ�, ���� �������� ����� ���� �ε������� �����´�.
           temp2.setIndex(findIndex(temp2));
       }
       //������ ��� �����ϴ� �����鿡 ���ؼ�
       HeadNodes[temp1.getIndex()].push_back(temp2);
       HeadNodes[temp2.getIndex()].push_back(temp1);    //������̹Ƿ�
    }
    numOfVertex=index;  
    //�뼱�� �ϼ�!
}
//============================================================================
void Graph::findShortestWay(int fromIndex, int toIndex){       //���ͽ�Ʈ�� �˰���,���Ḯ��Ʈ,�켱���� ť�� �̿�
    dist.clear(); dist.reserve(vertex.size()); dist.resize(vertex.size(),INF);
    //������ ���� ã�µ� �־, �ִܰŸ� ã�⸦ �� �� �ϴµ�, ���� ����� �����ִٸ�
    //�ִܰ�� ã�µ� �־ ������ �߻��Ѵ�.
    route.clear(); route.reserve(vertex.size()); route.resize(vertex.size(),-1);
    dist[fromIndex]=0;  //���������� �ð� 0
    priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > pq;
    //�켱���� ť�� pair�� ��� first�� �������� ����, <����ġ, �ε���> ���̴�.
    //�켱����ť<�ڷ���,����ü(��� vector<�ڷ���>),�񱳿�����(�⺻���� less<�ڷ���>)
    //greater�� �ϸ� ������������ ����, �⺻������ �ϸ� ��������
    pq.push(make_pair(0,fromIndex));
    //(0,����) ���� �־�д�. 
    while(!pq.empty()){
        int curDist=pq.top().first;
        int curIndex=pq.top().second;
        pq.pop();
        if(dist[curIndex]<curDist) continue;    
        //ť�� ����Ǿ��ִ� ���� �������� �Ÿ��� dist�� ����Ǿ��ִ� �Ÿ����� ��ٸ�, 
        //�̹� �ִܰŸ��� �ƴϱ� ������ �ǳ� �ڴ�. �Ʒ��� �񱳰����� �����Ѵ�.
        for(int i=0;i<HeadNodes[curIndex].size();i++){  //���� ���� ����� ��� �������� �ð� ��
            int nextDist=curDist+HeadNodes[curIndex][i].getDist();
            //���� ������ ���� �������� �ð��� ��
            int nextIndex=HeadNodes[curIndex][i].getIndex();
            //���� ���� �ε���
            if(nextDist<dist[nextIndex]){  
                //������� ���� �������� ���̰� ���� ���� ���İ��� �ͺ��� ��ٸ�,
                dist[nextIndex]=nextDist;   //���̸� �ݿ��ϰ�
                route[nextIndex]=curIndex;  //��ο� ������ �ε����� �ݿ��Ѵ�.
                pq.push(make_pair(nextDist, nextIndex));
                //���� �ε����� ���� �˰����� �����ϱ� ���� ť�� �־�д�.
            }
        }
    }
}
//============================================================================
void Graph::printShortestWay(int fromIndex, int toIndex){
    int minute, second;
    minute=dist[toIndex]/2;
    second=(dist[toIndex]%2)*30;
    int i=toIndex;
    stack<int> routeStack;      
    //��θ� toIndex���� �������� fromIndex���� Ž���� �����̰�
    //����� �� ���߿� �� ���� ���� ���;��Ѵ�.
    routeStack.push(i);
    while(route[i]!=-1){
        i=route[i];
        if(vertex[routeStack.top()].getStation()!=vertex[i].getStation())
            routeStack.push(i);
        
    }
    while(!routeStack.empty()){
        i=routeStack.top(); routeStack.pop();
        cout<<vertex[i]<<endl;
    }
    cout<<minute<<":";
    cout.fill('0');
    cout.width(2);
    cout<<second<<endl;   
}
//============================================================================
void Graph::findFairPoint(int terminal1, int terminal2){
    vector<int> temp;        //terminal1�� �������� ã�� �ִܰŸ��� ������ ����
    temp.resize((int)dist.size());      //temp�� ����� dist�� �����ŭ
    findShortestWay(terminal1, terminal2);
    copy(dist.begin(),dist.end(),temp.begin());
    findShortestWay(terminal2, terminal1);
    vector<int> dif;
    dif.resize(dist.size(),INF);
    int minIndex=-1;    //Index�� �����ϼ� ������ ����Ǿ��� �ݿ�
    int minDif=INF;     //�� �ɸ� �ð� ���� �ּҸ� ���� ����
    vector<int>::iterator itr=dist.begin(); //dist�� temp�� dif�� ũ��� ����.
    for(int i=0; i<numOfVertex ; ++i){
        dif[i]=dist[i]-temp[i];
        if(dif[i]<0) dif[i]=-dif[i];
        if(minDif>dif[i]){
            minDif=dif[i];  minIndex=i;
        }
    }
    cout<<vertex[minIndex]<<endl;     //���� ���
    
    int tempMinute,tempSecond;
    int distMinute,distSecond;
    tempMinute=temp[minIndex]/2; tempSecond=temp[minIndex]%2*30;
    distMinute=dist[minIndex]/2; distSecond=dist[minIndex]%2*30;

    if(temp[minIndex]>dist[minIndex]){      //ũ�⿡ ���� �ɸ��ð� ���
        cout<<tempMinute<<":";
        cout.fill('0');
        cout.width(2);
        cout<<tempSecond<<endl;
        cout<<distMinute<<":";
        cout.fill('0');
        cout.width(2);
        cout<<distSecond<<endl;
    }    
    else{
        cout<<distMinute<<":";
        cout.fill('0');
        cout.width(2);
        cout<<distSecond<<endl;
        cout<<tempMinute<<":";
        cout.fill('0');
        cout.width(2);
        cout<<tempSecond<<endl;
    }
}    
//============================================================================