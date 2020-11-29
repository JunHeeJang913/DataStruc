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
        if(x==station){     //만약 존재한다면 참을 반환
            return true;
        }
    }
    return false;   //다 돌아봤는데 없으면 거짓을 반환
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
       temp2.setDist(temp1);  temp1.setDist(temp2); //길이도 설정
       //만약 temp1, temp2가 새 정점이라면 정점 집합에 추가.
       if(isVertexExist(temp1)==false){
           HeadNodes.resize(index+1);
           temp1.setIndex(index);
           vertex.push_back(temp1);
           index++;
       }
       else{    //같은 역(호선, 역 이름)이 있다면, 같은 정점으로 만들기 위해 인덱스까지 가져온다. 
           temp1.setIndex(findIndex(temp1));
       }
       if(isVertexExist(temp2)==false){
           HeadNodes.resize(index+1);
           temp2.setIndex(index);
           vertex.push_back(temp2);
           index++;
       }
       else{    //같은 역(호선, 역 이름)이 있다면, 같은 정점으로 만들기 위해 인덱스까지 가져온다.
           temp2.setIndex(findIndex(temp2));
       }
       //이제는 모두 존재하는 정점들에 대해서
       HeadNodes[temp1.getIndex()].push_back(temp2);
       HeadNodes[temp2.getIndex()].push_back(temp1);    //양방향이므로
    }
    numOfVertex=index;  
    //노선도 완성!
}
//============================================================================
void Graph::findShortestWay(int fromIndex, int toIndex){       //다익스트라 알고리즘,연결리스트,우선순위 큐를 이용
    dist.clear(); dist.reserve(vertex.size()); dist.resize(vertex.size(),INF);
    //공평한 점을 찾는데 있어서, 최단거리 찾기를 두 번 하는데, 전의 결과가 남아있다면
    //최단경로 찾는데 있어서 문제가 발생한다.
    route.clear(); route.reserve(vertex.size()); route.resize(vertex.size(),-1);
    dist[fromIndex]=0;  //시점까지의 시간 0
    priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > pq;
    //우선순위 큐는 pair의 경우 first를 기준으로 정렬, <가중치, 인덱스> 쌍이다.
    //우선순위큐<자료형,구현체(대게 vector<자료형>),비교연산자(기본값은 less<자료형>)
    //greater로 하면 오름차순으로 정렬, 기본값으로 하면 내림차순
    pq.push(make_pair(0,fromIndex));
    //(0,시점) 쌍을 넣어둔다. 
    while(!pq.empty()){
        int curDist=pq.top().first;
        int curIndex=pq.top().second;
        pq.pop();
        if(dist[curIndex]<curDist) continue;    
        //큐에 저장되어있던 현재 점까지의 거리가 dist에 저장되어있는 거리보다 길다면, 
        //이미 최단거리가 아니기 때문에 건너 뛴다. 아래의 비교과정을 생략한다.
        for(int i=0;i<HeadNodes[curIndex].size();i++){  //현재 역과 연결된 모든 역까지의 시간 비교
            int nextDist=curDist+HeadNodes[curIndex][i].getDist();
            //지금 점에서 다음 점까지의 시간의 합
            int nextIndex=HeadNodes[curIndex][i].getIndex();
            //다음 점의 인덱스
            if(nextDist<dist[nextIndex]){  
                //현재까지 구한 다음점의 길이가 지금 점을 거쳐가는 것보다 길다면,
                dist[nextIndex]=nextDist;   //길이를 반영하고
                route[nextIndex]=curIndex;  //경로에 현재의 인덱스를 반영한다.
                pq.push(make_pair(nextDist, nextIndex));
                //다음 인덱스에 대해 알고리즘을 적용하기 위해 큐에 넣어둔다.
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
    //경로를 toIndex부터 역순으로 fromIndex까지 탐색할 예정이고
    //출력할 때 나중에 들어간 것이 먼저 나와야한다.
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
    vector<int> temp;        //terminal1을 기준으로 찾은 최단거리를 저장할 예정
    temp.resize((int)dist.size());      //temp의 사이즈를 dist의 사이즈만큼
    findShortestWay(terminal1, terminal2);
    copy(dist.begin(),dist.end(),temp.begin());
    findShortestWay(terminal2, terminal1);
    vector<int> dif;
    dif.resize(dist.size(),INF);
    int minIndex=-1;    //Index는 음수일수 없으니 어찌되었든 반영
    int minDif=INF;     //두 걸린 시간 차의 최소를 담을 변수
    vector<int>::iterator itr=dist.begin(); //dist와 temp와 dif의 크기는 같다.
    for(int i=0; i<numOfVertex ; ++i){
        dif[i]=dist[i]-temp[i];
        if(dif[i]<0) dif[i]=-dif[i];
        if(minDif>dif[i]){
            minDif=dif[i];  minIndex=i;
        }
    }
    cout<<vertex[minIndex]<<endl;     //중점 출력
    
    int tempMinute,tempSecond;
    int distMinute,distSecond;
    tempMinute=temp[minIndex]/2; tempSecond=temp[minIndex]%2*30;
    distMinute=dist[minIndex]/2; distSecond=dist[minIndex]%2*30;

    if(temp[minIndex]>dist[minIndex]){      //크기에 따라서 걸린시간 출력
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