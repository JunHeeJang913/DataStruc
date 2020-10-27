#include <iostream>
#include <stack>
using namespace std;

const int MAXSIZE = 100; // up to 100 by 100 maze allowed
bool maze[MAXSIZE + 2][MAXSIZE + 2];        //�̷� �迭, �׵θ� �۾��� ���� +2
bool mark[MAXSIZE + 1][MAXSIZE + 1] = {0};  //**�迭�� ��� ���Ҹ� �̷��� �ʱ�ȭ�� �� �ִ�, +!..?

enum directions {N,NE, E,SE,S, SW,W, NW};
struct offsets{
    int a, b;
} mov[8] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}}; //����ü offset �� ����صα�

struct Items{
    Items(int xx = 0, int yy = 0, int dd = 0) : x(xx), y(yy), dir(dd) {}
    int x, y, dir;
};


template <class T>
ostream &operator<<(ostream &os, stack<T> &s){
    // ������ ������ �������� ���
    // �������=������ �ϳ��� ���� �ٸ� �ӽ� ���ÿ� �־� ������ ��,
    // ���������� �� �ӽ� ���ÿ��� �ϳ��� ���� ����ϸ� ��
    stack<T> tempStack;
    /*
        �ӽý��ÿ� ����. 
        ���ǻ���: s�� �������̹Ƿ� s���� pop�ϸ� ������ �������
        -->�ٽ� s�� ������־����.
    */
    while(s.empty()!=true){
        tempStack.push(s.top());
        s.pop();
    }
    //os�� �ϳ��� ���� �־��ְ� s�� �������.
    while(tempStack.empty()!=true){
        os<<" -> "<<tempStack.top();
        s.push(tempStack.top());
        tempStack.pop();
    }
    return os;
}

ostream &operator<<(ostream &os, Items &item){
    static int count = 0;       
    //**���������� ��� ����ֱ⶧���� path()���� exit���� �ÿ� ����ϴ� �͵� �ٹٲٱⰡ �����ϰ� ���ش�!
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
        tempItem=pathStack.top();  pathStack.pop(); //unstack,�������or�ǵ��ư���
        int i=tempItem.x;   int j=tempItem.y;   int d=tempItem.dir;
        while(d<8){         //(i,j)����(g,h)�̵�
            int g = i+mov[d].a; int h = j + mov[d].b;   //the point where we try to go
            if((g==m)&&(h==p)){         //reached exit
                cout<<pathStack;        //  print path
                tempItem.x = i; tempItem.y = j; cout << " -> " << tempItem;     //print present point::cout<<" -> ("<<i<<","<<j<<")"�� ����..
                tempItem.x = m; tempItem.y = p; cout << " -> " << tempItem << endl;     //print next point
                cout<<"\n#node visited = "<<numOfVisitedNode+1<<" out of "<<m*p<<endl;  //���� �������� �湮 ���߱⶧���� +1��.
                return;
            }
            if((maze[g][h]==0)&&(mark[g][h]==0)){ //next point is new, possible point **!something<==>something==0, ������������
                mark[g][h]=1;   numOfVisitedNode++;
                tempItem.x=i;tempItem.y=j;tempItem.dir=d+1;//present point, if failed, next trial direction
                pathStack.push(tempItem);//stack�Ѵ�
                i=g;j=h;d=N;    //N(=0)������� �ð�������� �õ��غ���.
            }       //not understand yet
            else{
                d++;   
            }
        }
        //8������ �� �ѷ���������, �� �� �ִ� ���� ����
    }
    cout<<"No path in maze"<<endl; 
}

void getdata(istream &is, int &m, int &p){ // �ڷ������� �о�鿩 maze�� �����Ѵ�.
    is >> m >> p;       //m,p�� �̷��� ũ��
    //�̷��� �׵θ��� 1�� �ѷ��ִ� �۾�
    for (int i = 0; i < m + 2; i++){
        maze[i][0] = 1;
        maze[i][p + 1] = 1;
    }
    for (int j = 1; j <= p; j++){
        maze[0][j] = 1;
        maze[m + 1][j] = 1;
    }
    //�̷� ���� �Է�.
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= p; j++)
            is >> maze[i][j];
}