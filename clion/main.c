#include "lex.yy.c"

int main()
{
    yyin = fopen("../2.txt", "r");
    yylex();
    return 0;
}