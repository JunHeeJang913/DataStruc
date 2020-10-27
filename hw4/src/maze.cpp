#include <iostream>
#include <stack>
using namespace std;

const int MAXSIZE = 100; // up to 100 by 100 maze allowed
bool maze[MAXSIZE + 2][MAXSIZE + 2];        //미로 배열, 테두리 작업을 위해 +2
bool mark[MAXSIZE + 1][MAXSIZE + 1] = {0};  //**배열의 모든 원소를 이렇게 초기화할 수 있다, +!..?

enum directions {N,NE, E,SE,S, SW,W, NW};
struct offsets{
    int a, b;
} mov[8] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}}; //구조체 offset 잘 기억해두기

struct Items{
    Items(int xx = 0, int yy = 0, int dd = 0) : x(xx), y(yy), dir(dd) {}
    int x, y, dir;
};


template <class T>
ostream &operator<<(ostream &os, stack<T> &s){
    // 스택의 내용을 역순으로 출력
    // 구현방법=내용을 하나씩 꺼내 다른 임시 스택에 넣어 저장한 후,
    // 최종적으로 그 임시 스택에서 하나씩 꺼내 출력하면 됨
    stack<T> tempStack;
    /*
        임시스택에 저장. 
        주의사항: s는 참조자이므로 s에서 pop하면 실제로 사라진다
        -->다시 s를 만들어주어야함.
    */
    while(s.empty()!=true){
        tempStack.push(s.top());
        s.pop();
    }
    //os에 하나씩 값을 넣어주고 s를 만들어줌.
    while(tempStack.empty()!=true){
        os<<" -> "<<tempStack.top();
        s.push(tempStack.top());
        tempStack.pop();
    }
    return os;
}

ostream &operator<<(ostream &os, Items &item){
    static int count = 0;       
    //**정적변수라서 계속 살아있기때문에 path()에서 exit도달 시에 출력하는 것도 줄바꾸기가 가능하게 해준다!
    os << "(" << item.x << "," << item.y << ")";
    count++;
    if ((count % 5) == 0)
        cout << endl;
    return os;
}

void Path(const int m, const int p){
    mark[1][1]=1;   // start at (1,1)
    stack<Items> pathStack; 
    Items tempItem(1,1,E);  
    pathStack.push(tempItem);
    int numOfVisitedNode=0;   
    while(pathStack.empty()!=true){         //stack is not empty
        tempItem=pathStack.top();  pathStack.pop(); //unstack,정보얻기or되돌아가기
        int i=tempItem.x;   int j=tempItem.y;   int d=tempItem.dir;
        while(d<8){         //(i,j)에서(g,h)이동
            int g = i+mov[d].a; int h = j + mov[d].b;   //the point where we try to go
            if((g==m)&&(h==p)){         //reached exit
                cout<<pathStack;        //  print path
                tempItem.x = i; tempItem.y = j; cout << " -> " << tempItem;     //print present point::cout<<" -> ("<<i<<","<<j<<")"도 가능..
                tempItem.x = m; tempItem.y = p; cout << " -> " << tempItem << endl;     //print next point
                cout<<"\n#node visited = "<<numOfVisitedNode+1<<" out of "<<m*p<<endl;  //아직 도착지는 방문 안했기때문에 +1만.
                return;
            }
            if((maze[g][h]==0)&&(mark[g][h]==0)){ //next point is new, possible point **!something<==>something==0, 착각하지말자
                mark[g][h]=1;   numOfVisitedNode++;
                tempItem.x=i;tempItem.y=j;tempItem.dir=d+1;//present point, if failed, next trial direction
                pathStack.push(tempItem);//stack한다
                i=g;j=h;d=N;    //N(=0)방향부터 시계방향으로 시도해본다.
            }       //not understand yet
            else{
                d++;   
            }
        }
        //8방향을 다 둘러보았지만, 갈 수 있는 곳이 없음
    }
    cout<<"No path in maze"<<endl; 
}

void getdata(istream &is, int &m, int &p){ // 자료파일을 읽어들여 maze에 저장한다.
    is >> m >> p;       //m,p는 미로의 크기
    //미로의 테두리를 1로 둘러주는 작업
    for (int i = 0; i < m + 2; i++){
        maze[i][0] = 1;
        maze[i][p + 1] = 1;
    }
    for (int j = 1; j <= p; j++){
        maze[0][j] = 1;
        maze[m + 1][j] = 1;
    }
    //미로 내용 입력.
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= p; j++)
            is >> maze[i][j];
}