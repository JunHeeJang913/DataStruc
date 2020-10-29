#include <iostream>
#include <stack>
#include "post.h"
using namespace std;
bool Token::operator==(char b) { return len == 1 && str[0] == b; }
bool Token::operator!=(char b) { return len != 1 || str[0] != b; }
Token::Token() {}
Token::Token(char c) : len(1), type(c){
    str = new char[1];
    str[0] = c;
} // default type = c itself
Token::Token(char c, char c2, int ty) : len(2), type(ty){
    str = new char[2];
    str[0] = c;
    str[1] = c2;
}
Token::Token(char *arr, int l, int ty = ID) : len(l), type(ty){//기본 타입은 ID, ID나 NUM만 가능
    str = new char[len + 1];    //마지막에 \0을 넣기 위해.
    for (int i = 0; i < len; i++)
        str[i] = arr[i];        //str에 복사
    str[len] = '\0';            //문자열 끝.
    if (type == NUM)            //피연산자가 수일경우
    {
        ival = arr[0] - '0';
        for (int i = 1; i < len; i++)
            ival = ival * 10 + arr[i] - '0';
    }
    else if (type == ID)        //피연산자가 A나 an77 같은 것이 경우
        ival = 0;
    else
        throw "must be ID or NUM";
}
bool Token::IsOperand()     //피연산자인가 아닌가?
{
    return type == ID || type == NUM;
}
ostream &operator<<(ostream &os, Token t)       //오버로딩
{
    if (t.type == UMINUS)       //unary minus
        os << "-u";
    else if (t.type == NUM)
        os << t.ival;
    else
        for (int i = 0; i < t.len; i++)
            os << t.str[i];
    os << " ";
    return os;
}
bool GetID(Expression &e, Token &tok){      //ID토큰 생성, 후에 나올 NextToken함수에서 판별용으로 사용
    char arr[MAXLEN];
    int idlen = 0;
    char c = e.str[e.pos];
    if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))    //알파벳이 아니면
        return false;

    arr[idlen++] = c;   //arr[0]에 c를 대입하고 idlen=1;
    e.pos++;        //pos+1

    while ((c = e.str[e.pos]) >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9')
    {
        arr[idlen++] = c;
        e.pos++;
    }
    arr[idlen] = '\0';
    tok = Token(arr, idlen, ID); // return an ID
    return true;
}

bool GetInt(Expression &e, Token &tok){         //GetID와 비슷한 기능.
    char arr[MAXLEN];
    int idlen = 0;
    char c = e.str[e.pos];
    if (!(c >= '0' && c <= '9'))    //숫자가 아니면
        return false;
    arr[idlen++] = c;   //arr[0]에 c를 대입하고 idlen=1;
    e.pos++;        //pos+1
    while ((c = e.str[e.pos]) >= '0' && c <= '9')
    {
        arr[idlen++] = c;
        e.pos++;
    }
    arr[idlen] = '\0';
    tok = Token(arr, idlen, NUM); // return an NUM
    return true;
}

void SkipBlanks(Expression &e){
    char c;
    while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t'))
        e.pos++;
}
bool TwoCharOp(Expression &e, Token &tok){
    // 7가지 두글자 토큰들 <= >= == != && || -u을 처리
    char c = e.str[e.pos];
    char c2 = e.str[e.pos + 1];
    int op; // LE GE EQ NE AND OR UMINUS
    if (c == '<' && c2 == '=')
        op = LE;
    else if(c == '>' && c2 == '=')                // .각 두글자 토큰에 대해 알맞은 type값을 op에 저장
        op  = GE;
    else if(c == '=' && c2 == '=')
        op = EQ;
    else if(c == '!' && c2 == '=')
        op = NE;
    else if(c == '&' && c2 == '&')
        op = AND;
    else if(c == '|' && c2 == '|')
        op = OR;
    else if(c == '-' && c2 == 'u')      
        op = UMINUS;
    else return false; // 맞는 두글자 토큰이 아니면 false를 return
    tok = Token(c, c2, op);
    e.pos += 2;
    return true;
}
bool OneCharOp(Expression &e, Token &tok)
{
    char c = e.str[e.pos];
    if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' ||
        c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=')
    {
        tok = Token(c);
        e.pos++;
        return true;
    }
    return false;
}
Token NextToken(Expression &e)  //여기서 토큰을 생성
{
    static bool oprrFound = true; // 종전에 연산자 발견되었다고 가정.   
    Token tok;
    SkipBlanks(e);      // skip blanks if any
    if (e.pos == e.len) // No more token left in this expression
    {
        oprrFound = true;
        return Token('#');
    }
    if (GetID(e, tok) || GetInt(e, tok))
    {
        oprrFound = false;
        return tok;
    }
    if (TwoCharOp(e, tok) || OneCharOp(e, tok))
    {
        if (tok.type == '-' && (oprrFound==true)) //operator후 -발견->oprrfound를 사용하면...  
            tok = Token('-', 'u', UMINUS);              // unary minus(-u)로바꾸시오    //e.str[e.pos-2]는 왜..?
        oprrFound=true;
        return tok;
    }
    throw "Illegal Character Found";
}
int icp(Token &t){ // in-coming priority    Fig 3.12참고
    int ty = t.type;
    if(ty=='(')//'('면 0
        return 0;
    else if(ty==UMINUS||ty=='!')//UMINUS나 '!'면 1
        return 1;
    else if(ty=='*'||ty=='/'||ty=='%')//'*'나 '/'나 '%'면 2
        return 2;
    else if(ty=='+'||ty=='-')//‘+’나 '-'면 3
        return 3;
    else if(ty=='<'||ty=='>'||ty==LE||ty==GE)//'<'나 '>'나 LE나 GE면 4
        return 4;
    else if(ty==NE||ty==EQ)//EQ나 NE면 5
        return 5;
    else if(ty==AND)//AND면 6
        return 6;
    else if(ty==OR)//OR이면 7
        return 7;
    else if(ty=='=')//'='이면 8
        return 8;
    else if(ty=='#')//'#'면 9
        return 9;
    /*switch(ty){
        case '(':   
            return 0;
            break;
        case UMINUS:    
        case '!':
            return 1;break;
        case '*':       
        case '/':
        case '%':
            return 2;break;
        case '+':   
        case '-':
            return 3;break;
        case '>':   
        case '<':
        case LE:
        case GE:
            return 4;break;
        case EQ:    
        case NE:
            return 5;break;
        case AND:   
            return 6;break;
        case OR:    
            return 7;break;
        case '=':   
            return 8;break;
        case '#':   
            return 9;break;
        default:
            break;
    }*/
}
int isp(Token &t) // in-stack priority
{
    int ty = t.type;
    //stack 에서의 우선순위 결정; 괄호를 제하고는 비슷한듯하다.
    if(ty=='(')//'('면 9, 
        return 9;
    else if(ty==UMINUS||ty=='!')//UMINUS나 '!'면 1
        return 1;
    else if(ty=='*'||ty=='/'||ty=='%')//'*'나 '/'나 '%'면 2
        return 2;
    else if(ty=='+'||ty=='-')//‘+’나 '-'면 3
        return 3;
    else if(ty=='<'||ty=='>'||ty==LE||ty==GE)//'<'나 '>'나 LE나 GE면 4
        return 4;
    else if(ty==NE||ty==EQ)//EQ나 NE면 5
        return 5;
    else if(ty==AND)//AND면 6
        return 6;
    else if(ty==OR)//OR이면 7
        return 7;
    else if(ty=='=')//'='이면 8
        return 8;
    else if(ty=='#')//'#'면 10
        return 9;
}     
/*  
    if,else if 문과는 다르게 switch-case문을 쓰면 
    default인 경우를 만들어 return값을 주어야 gcc에서
    경고를 안한다.
    control reaches end of non-void function [-Wreturn-type]
    ->if-else문을 쓰는 것이 나을 것 같다.
    ->if-else도 저 경고문을 내보낸다... default든 else든 끝까지 써서 return을 해야 안뜨는 듯
*/
void Postfix(Expression e)  //program 3.19
{
    // infix expression e를 postfix form으로 바꾸어 출력
    // e에 토큰이 없으면 NextToken은 ‘#’ 토큰을 반환한다.
    // 스택의 밑에도 ‘#’를 넣고 시작한다.-->이게 없으면 아래의 문장들을
    // 실행할 때 공백인 상태에서 스택의 탑에 접근하는 경우가 생긴다.
    stack<Token> tokenStack;
    Token y;
    tokenStack.push('#');
    for(Token x = NextToken(e);x!='#';x=NextToken(e)){
        if(x.IsOperand()==true)     //x is operand
            cout<<x;
        else if(x==')'){         //x is parenthese, unstack until '('
            for(y=tokenStack.top();y!='(';y=tokenStack.top()){
                cout<<y;    tokenStack.pop();
            }
            tokenStack.pop();       //unstack '('
        }
        else{   //x is an operator
            for(y=tokenStack.top();isp(y)<=icp(x);y=tokenStack.top()){
                cout<<y;
                tokenStack.pop();
            }
            //tokenStack.push(y);       교재와는 달리 last y가 unstack되지 않는다.
            tokenStack.push(x);
        }           
    }
    while(tokenStack.top()!='#'){
        cout<<tokenStack.top();
        tokenStack.pop();
    }
    cout<<endl;     //pdf의 예상출력처럼 보기위해 개행
}