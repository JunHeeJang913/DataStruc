#ifndef POSTFIX_H
#define POSTFIX_H
// token types for non one-char tokens
#define ID 257              //여기서 정의한 것들이 타입이 된다. 피연산자가 A거나..an77같은것의 type인듯
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
    int pos;    //expression은 문장 전부를 받기 때문에 pos로 위치를 계속해서 기록해주는 것!
    int len;
};

struct Token{
    bool operator==(char);
    bool operator!=(char);
    Token();
    Token(char);             // 1-char token: type equals the token itself  
    Token(char, char, int);  // 2-char token(e.g. <=) & its type(e.g.LE)    
    Token(char *, int, int); // operand with its length & type(defaulted to ID) 
    bool IsOperand();        // true if the token type is ID or NUM 피연산자인가?
    int type;                // ascii code for 1-char op; predefined for other tokens
    char *str;               // token value; cpp파일의 생성자 부분과 비교해서 보면 이해 가능
    int len;                 // length of str
    int ival;                // used to store an integer for type NUM; init to 0 for ID; int_value인듯하다.
                            // 문자열로 받은 수를 정수로 나타내기위함인듯.
};

using namespace std;
ostream &operator<<(ostream &, Token);
Token NextToken(Expression &, bool); // 2nd arg=true for infix expression
#endif