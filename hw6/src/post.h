#ifndef POSTFIX_H
#define POSTFIX_H
// token types for non one-char tokens
#define ID 257              //���⼭ ������ �͵��� Ÿ���� �ȴ�. �ǿ����ڰ� A�ų�..an77�������� type�ε�
#define NUM 258
#define EQ 259
#define NE 260
#define GE 261
#define LE 262
#define AND 263
#define OR 264
#define UMINUS 265
#define MAXLEN 80
#include <iostream>
struct Expression{
    Expression(char *s) : str(s), pos(0){
        for (len = 0; str[len] != '\0'; len++);
    }
    char *str;
    int pos;    //expression�� ���� ���θ� �ޱ� ������ pos�� ��ġ�� ����ؼ� ������ִ� ��!
    int len;
};

struct Token{
    bool operator==(char);
    bool operator!=(char);
    Token();
    Token(char);             // 1-char token: type equals the token itself  
    Token(char, char, int);  // 2-char token(e.g. <=) & its type(e.g.LE)    
    Token(char *, int, int); // operand with its length & type(defaulted to ID) 
    bool IsOperand();        // true if the token type is ID or NUM �ǿ������ΰ�?
    int type;                // ascii code for 1-char op; predefined for other tokens
    char *str;               // token value; cpp������ ������ �κа� ���ؼ� ���� ���� ����
    int len;                 // length of str
    int ival;                // used to store an integer for type NUM; init to 0 for ID; int_value�ε��ϴ�.
                            // ���ڿ��� ���� ���� ������ ��Ÿ���������ε�.
};

using namespace std;
ostream &operator<<(ostream &, Token);
Token NextToken(Expression &, bool); // 2nd arg=true for infix expression
#endif