#include "subway.h"
using namespace std;
//============================================================================
ostream& operator <<(ostream& os, Vertex& v){
    os<<v.getStation()<<endl;
    return os;
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
        if(x==station){     //만약 존재한다면 참을 반환
            return true;
        }
    }
    return false;   //다 돌아봤는데 없으면 거짓을 반환
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
    int n = 2*numLine;  //역의 최대 개수는 numline*2;
    int index=0;
    HeadNodes = new vector<Vertex>[n];
    while(f){       //그래프 만드는 과정
        f>>line1; f>>stat1; f>>line2; f>>stat2;
        Vertex temp1(line1,stat1); Vertex temp2(line2,stat2);
        /*
        새로운 정점이라면, 추가
        간선은 양방향에 유의(모두가 새로운 간선이므로 그냥 넣으면 됨)
        토대로 인접리스트 형태의 그래프 만들기
        ex)역이름이 입력되면, vertex에서 원소를 찾아서 그 인덱스(i)를 반환하고
            그 인덱스에 위치한 HeadNodes[i]에서 찾으면 된다.
        */
       temp2.setWeight(temp1);  temp1.setWeight(temp2); //길이도 설정
       //만약 temp1, temp2가 새 정점이라면 정점 집합에 추가.
       if(isVertexExist(temp1)==false){
           temp1.setIndex(index);
           vertex[index]=temp1;
           index++;
       }
       else{    //같은 역(호선, 역 이름)이 있다면, 같은 정점으로 만들기 위해 인덱스까지 가져온다. 
           temp1.setIndex(findIndex(temp1));
       }
       if(isVertexExist(temp2)==false){
           temp2.setIndex(index);
           vertex[index]=temp1;
           index++;
       }
       else{    //같은 역(호선, 역 이름)이 있다면, 같은 정점으로 만들기 위해 인덱스까지 가져온다.
           temp2.setIndex(findIndex(temp2));
       }
       //이제는 모두 존재하는 정점들에 대해서
       HeadNodes[temp1.getIndex()].push_back(temp2);
       HeadNodes[temp2.getIndex()].push_back(temp1);    //양방향이므로
       //temp1에 대해서
       /*if(isVertexExist(temp1)==true){
           HeadNodes[findIndex(temp1)].push_back(temp2);
       }
       else{        //새로운 정점
            vertex.push_back(temp1);
            HeadNodes[findIndex(temp1)].push_back(temp2);
       }
       //temp2에 대해서
       if(isVertexExist(temp2)==true){
           HeadNodes[findIndex(temp2)].push_back(temp1);
       }
       else{        //새로운 정점
            vertex.push_back(temp2);
            HeadNodes[findIndex(temp2)].push_back(temp1);
       }*/
    }
    for(int i=0;i<index+1;i++){
        dist[i]=INF;
    }//일단 무한대로 채운다.    
    //노선도 완성!
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
void Graph::findShortestWay(int fromIndex, int toIndex){       //다익스트라 알고리즘,연결리스트,우선순위 큐를 이용
    dist[fromIndex]=0;
    priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > pq;
    queue<Vertex> tempRoute;
    //우선순위 큐는 pair의 경우 first를 기준으로 정렬, <가중치, 인덱스> 쌍이다.
    //우선순위큐<자료형,구현체(대게 vector<자료형>),비교연산자(기본값은 less<자료형>)
    //greater로 하면 오름차순으로 정렬, 기본값으로 하면 내림차순
    pq.push(make_pair(0,fromIndex));
    while(!pq.empty()){
        int distance = pq.top().first;
        int current = pq.top().second;
        pq.pop();
        if(dist[current]<distance) continue;
        for(int i=0;i<HeadNodes[current].size();i++){
            int nextDist = distance+HeadNodes[current][i].getWeight();
            int next = HeadNodes[current][i].getIndex();
            if(nextDist < dist[next]){  //더 빨라진다면
                dist[next] = nextDist;
                pq.push(make_pair(nextDist, next));
            }
        }
    }
}
//============================================================================
void Graph::printShortestWay(int fromIndex, int toIndex){
    int minute, second;
    minute = dist[toIndex]/2;
    second = (dist[toIndex]%2)*30;
    int i=fromIndex;
    while(route[i]!=toIndex){
        cout<<vertex[i]<<endl;;
        i=route[i];
    }
    cout<<vertex[toIndex]<<endl;
    cout<<minute<<":"<<second<<endl;   
}
//============================================================================
string Graph::findFairPoint(int terminal1, int terminal2){
    vector<int> temp;        //terminal1을 기준으로 찾은 최단거리를 저장할 예정
    temp.resize((int)dist.size());      //temp의 사이즈를 dist의 사이즈만큼
    findShortestWay(terminal1, terminal2);
    copy(dist.begin(),dist.end(),temp.begin());
    findShortestWay(terminal2, terminal1);
    vector<int> dif;
    dif.resize((int)dist.size());
    int minIndex=-1;    //Index는 음수일수 없으니 어찌되었든 반영
    int minDif=INF;     //두 걸린 시간 차의 최소를 담을 변수
    vector<int>::iterator itr=dist.begin(); //dist와 temp와 dif의 크기는 같다.
    for(int i=0; itr!=dist.end(); itr+i){
        dif[i]=dist[i]-temp[i];
        if(dif[i]<0) dif[i]=-dif[i];
        if(minDif>dif[i]){
            minDif=dif[i];  minIndex=i;
        }
    }
    cout<<vertex[minIndex]<<endl;     //중점 출력
    
    int tempMinute,tempSecond;
    int distMinute,distSecond;
    tempMinute=temp[minIndex]/2; tempSecond=temp[minIndex]%2;
    distMinute=dist[minIndex]/2; distSecond=dist[minIndex]%2;

    if(temp[minIndex]>dist[minIndex]){      //크기에 따라서 걸린시간 출력
        cout<<tempMinute<<":"<<tempSecond<<endl;
        cout<<distMinute<<":"<<distSecond<<endl;
    }    
    else{
        cout<<distMinute<<":"<<distSecond<<endl;
        cout<<tempMinute<<":"<<tempSecond<<endl;
    }
}    
//============================================================================
