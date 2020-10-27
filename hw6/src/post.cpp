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
Token::Token(char *arr, int l, int ty = ID) : len(l), type(ty){//�⺻ Ÿ���� ID, ID�� NUM�� ����
    str = new char[len + 1];    //�������� \0�� �ֱ� ����.
    for (int i = 0; i < len; i++)
        str[i] = arr[i];        //str�� ����
    str[len] = '\0';            //���ڿ� ��.
    if (type == NUM)            //�ǿ����ڰ� ���ϰ��
    {
        ival = arr[0] - '0';
        for (int i = 1; i < len; i++)
            ival = ival * 10 + arr[i] - '0';
    }
    else if (type == ID)        //�ǿ����ڰ� A�� an77 ���� ���� ���
        ival = 0;
    else
        throw "must be ID or NUM";
}
bool Token::IsOperand()     //�ǿ������ΰ� �ƴѰ�?
{
    return type == ID || type == NUM;
}
ostream &operator<<(ostream &os, Token t)       //�����ε�
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
bool GetID(Expression &e, Token &tok){      //ID��ū ����. �Ŀ� ���� NextToken�Լ����� �Ǻ������� ���
    char arr[MAXLEN];
    int idlen = 0;
    char c = e.str[e.pos];
    if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))    //���ĺ��� �ƴϸ�...
        return false;
    arr[idlen++] = c;   //arr[0]�� c�� �����ϰ� idlen=1;
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

bool GetInt(Expression &e, Token &tok){         //GetID�� ����� ���.
    char arr[MAXLEN];
    int idlen = 0;
    char c = e.str[e.pos];
    if (!(c >= '0' && c <= '9'))    //���ڰ� �ƴϸ�... Ǯ����� �ְ�����..
        return false;
    arr[idlen++] = c;   //arr[0]�� c�� �����ϰ� idlen=1;
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
    // 7���� �α��� ��ū�� <= >= == != && || -u�� ó��
    char c = e.str[e.pos];
    char c2 = e.str[e.pos + 1];
    int op; // LE GE EQ NE AND OR UMINUS
    if (c == '<' && c2 == '=')
        op = LE;
    //EQ,NE,GE,LE(done),AND,OR,UMINUS;�����־���..
    else if(c == '>' && c2 == '=')                // .�� �α��� ��ū�� ���� �˸��� type���� op�� ����
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
    else return false; // �´� �α��� ��ū�� �ƴϸ� false�� return
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
Token NextToken(Expression &e)  //���⼭ ��ū�� ����
{
    static bool oprrFound = true; // ������ ������ �߰ߵǾ��ٰ� ����.
    Token tok;
    SkipBlanks(e);      // skip blanks if any
    if (e.pos == e.len) // No more token left in this expression
    {
        return Token('#');
    }
    if (GetID(e, tok) || GetInt(e, tok))
    {
        return tok;
    }
    if (TwoCharOp(e, tok) || OneCharOp(e, tok))
    {
        if (tok.type == '-' && e.str[e.pos - 2] == '-') //operator�� -�߰�
            tok = Token('-', 'u', UMINUS);              // unary minus(-u)�ιٲٽÿ�
        return tok;
    }
    throw "Illegal Character Found";
}
int icp(Token &t){ // in-coming priority
    int ty = t.type;
    switch(ty){
        case '(':   //'('�� 0
            return 0;
            break;
        case UMINUS:    //UMINUS�� '!'�� 1
        case '!':
            return 1;break;
        case '*':       //'*'�� '/'�� '%'�� 2
        case '/':
        case '%':
            return 2;break;
        case '+':   //��+���� '-'�� 3
        case '-':
            return 3;break;
        case '>':   //'<'�� '>'�� LE�� GE�� 4
        case '<':
        case LE:
        case GE:
            return 4;break;
        case EQ:    //EQ�� NE�� 5
        case NE:
            return 5;break;
        case AND:   //AND�� 6
            return 6;break;
        case OR:    //OR�̸� 7
            return 7;break;
        case '=':   //'='�̸� 8
            return 8;break;
        case '#':   //'#'�� 9
            return 9;break;
    }
}
int isp(Token &t) // in-stack priority
{
    int ty = t.type;
    //stack ������ �켱���� ����; ��ȣ�� ���ϰ�� ����ѵ��ϴ�.
    switch(ty){ 
        case UMINUS:    //UMINUS�� '!'�� 0
        case '!':
            return 0;break;
        case '*':       //'*'�� '/'�� '%'�� 1
        case '/':
        case '%':
            return 1;break;
        case '+':   //��+���� '-'�� 2
        case '-':
            return 2;break;
        case '>':   //'<'�� '>'�� LE�� GE�� 3
        case '<':
        case LE:
        case GE:
            return 3;break;
        case EQ:    //EQ�� NE�� 4
        case NE:
            return 4;break;
        case AND:   //AND�� 5
            return 5;break;
        case OR:    //OR�̸� 6
            return 6;break;
        case '=':   //'='�̸� 7
            return 7;break;
        case '(':   //'('�� 8
            return 8;
            break;
        case '#':   //'#'�� 9
            return 9;break;
    }
}
void Postfix(Expression e)
{
    // infix expression e�� postfix form���� �ٲپ� ���
    // e�� ��ū�� ������ NextToken�� ��#�� ��ū�� ��ȯ�Ѵ�.
    // ������ �ؿ��� ��#���� �ְ� �����Ѵ�.
}