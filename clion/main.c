#include "lex.yy.c"
#include "grammar_with_code.tab.c"
#include <stdio.h>
#include "treeToXML.h"

int main()
{
    yyin = fopen("../2.txt", "r");
    //yylex();
    yyparse();
    program_print(prg);
    program_xml(prg);

    return 0;
}