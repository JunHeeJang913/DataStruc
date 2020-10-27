#include <iostream>
#include <stack>
#include "post.h"
using namespace std;
bool Token::operator==(char b) { return len == 1 && str[0] == b; }
bool Token::operator!=(char b) { return len != 1 || str[0] != b; }
Token::Token() {}
Token::Token(char c) : len(1), type(c)
{

    str = new char[1];
    str[0] = c;
} // default type = c itself
Token::Token(char c, char c2, int ty) : len(2), type(ty)
{
    str = new char[2];
    str[0] = c;
    str[1] = c2;
}
Token::Token(char *arr, int l, int ty = ID) : len(l), type(ty)
{
    str = new char[len + 1];
    for (int i = 0; i < len; i++)
        str[i] = arr[i];
    str[len] = '\0';
    if (type == NUM)
    {
        ival = arr[0] - '0';
        for (int i = 1; i < len; i++)
            ival = ival * 10 + arr[i] - '0';
    }
    else if (type == ID)
        ival = 0;
    else
        throw "must be ID or NUM";
}
bool Token::IsOperand()
{
    return type == ID || type == NUM;
}
ostream &operator<<(ostream &os, Token t)
{
    if (t.type == UMINUS)
        os << "-u";
    else if (t.type == NUM)
        os << t.ival;
    else
        for (int i = 0; i < t.len; i++)
            os << t.str[i];
    os << " ";
    return os;
}
bool GetID(Expression &e, Token &tok)
{
    char arr[MAXLEN];
    int idlen = 0;
    char c = e.str[e.pos];
    if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))
        return false;
    arr[idlen++] = c;
    e.pos++;
    while ((c = e.str[e.pos]) >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9')
    {
        arr[idlen++] = c;
        e.pos++;
    }
    arr[idlen] = '\0';
    tok = Token(arr, idlen, ID); // return an ID
    return true;
}
bool GetInt(Expression &e, Token &tok)
{
    // �̺κ��� �ۼ��ϼ���
}
void SkipBlanks(Expression &e)
{
    char c;
    while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t'))
        e.pos++;
}
bool TwoCharOp(Expression &e, Token &tok)
{
    // 7���� �α��� ��ū�� <= >= == != && || -u�� ó��

    char c = e.str[e.pos];
    char c2 = e.str[e.pos + 1];
    int op; // LE GE EQ NE AND OR UMINUS
    if (c == '<' && c2 == '=')
        op = LE;
    else if                // .�� �α��� ��ū�� ���� �˸��� type���� op�� ����
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
Token NextToken(Expression &e)
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
int icp(Token &t)
{ // in-coming priority
    int ty = t.type;
    /* ty�� '('�� 0, UMINUS�� '!'�� 1,
'*'�� '/'�� '%'�� 2,
��+���� '-'�� 3,
'<'�� '>'�� LE�� GE�� 4, EQ�� NE�� 5,
AND�� 6,
OR�̸� 7,
'='�̸� 8,
'#'�� 9 �� return�Ѵ�.*/
}
int isp(Token &t) // in-stack priority
{
    int ty = t.type;
    //stack ������ �켱���� ����
}
void Postfix(Expression e)
{
    // infix expression e�� postfix form���� �ٲپ� ���
    // e�� ��ū�� ������ NextToken�� ��#�� ��ū�� ��ȯ�Ѵ�.
    // ������ �ؿ��� ��#���� �ְ� �����Ѵ�.
}