%option noyywrap
%option never-interactive

%%
[0-9]+ { printf("Found a number %d\n", atoi(yytext));}
%%
main()
{
  yylex();   
}
