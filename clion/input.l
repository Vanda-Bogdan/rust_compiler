%option noyywrap
%option never-interactive

%x CONST_STRING
%x MULTILINE_COMMENT
%x ONELINE_COMMENT
%x CHAR

DIGIT [0-9]

%{
#include <stdio.h>
#include <string.h>
char buffer[1000];
int remove_char(char *s, int pos);
void remove_underline();
int int_buffer;
%}

%%

as { printf("(%s) - Found KW_AS\n", yytext); }
break { printf("(%s) - Found KW_BREAK\n", yytext); }
const { printf("(%s) - Found KW_CONST\n", yytext); }
continue { printf("(%s) - Found KW_CONTINUE\n", yytext); }
crate { printf("(%s) - Found KW_CRATE\n", yytext); }
else { printf("(%s) - Found KW_ELSE\n", yytext); }
enum { printf("(%s) - Found KW_ENUM\n", yytext); }
extern { printf("(%s) - Found KW_EXTERN\n", yytext); }
false { printf("(%s) - Found KW_FALSE\n", yytext); }
fn { printf("(%s) - Found KW_FN\n", yytext); }
for { printf("(%s) - Found KW_FOR\n", yytext); }
if { printf("(%s) - Found KW_IF\n", yytext); }
impl { printf("(%s) - Found KW_IMPL\n", yytext); }
in { printf("(%s) - Found KW_IN\n", yytext); }
let { printf("(%s) - Found KW_LET\n", yytext); }
loop { printf("(%s) - Found KW_LOOP\n", yytext); }
match { printf("(%s) - Found KW_MATCH\n", yytext); }
mod { printf("(%s) - Found KW_MOD\n", yytext); }
move { printf("(%s) - Found KW_MOVE\n", yytext); }
mut { printf("(%s) - Found KW_MUT\n", yytext); }
pub { printf("(%s) - Found KW_PUB\n", yytext); }
ref { printf("(%s) - Found KW_REF\n", yytext); }
return { printf("(%s) - Found KW_RETURN\n", yytext); }
self { printf("(%s) - Found KW_SELFVALUE\n", yytext); }
Self { printf("(%s) - Found KW_SELFTYPE\n", yytext); }
static { printf("(%s) - Found KW_STATIC\n", yytext); }
struct { printf("(%s) - Found KW_STRUCT\n", yytext); }
super { printf("(%s) - Found KW_SUPER\n", yytext); }
trait { printf("(%s) - Found KW_TRAIT\n", yytext); }
true { printf("(%s) - Found KW_TRUE\n", yytext); }
type { printf("(%s) - Found KW_TYPE\n", yytext); }
unsafe { printf("(%s) - Found KW_UNSAFE\n", yytext); }
use { printf("(%s) - Found KW_USE\n", yytext); }
where { printf("(%s) - Found KW_WHERE\n", yytext); }
while { printf("(%s) - Found KW_WHILE\n", yytext); }
async { printf("(%s) - Found KW_ASYNC\n", yytext); }
await { printf("(%s) - Found KW_AWAITE\n", yytext); }
dyn { printf("(%s) - Found KW_DYN\n", yytext); }
i32 { printf("(%s) - Found KW_INTEGER32\n", yytext); }
String { printf("(%s) - Found KW_STRING\n", yytext); }
char { printf("(%s) - Found KW_CHAR\n", yytext); }
bool { printf("(%s) - Found KW_BOOLEAN\n", yytext); }

\" {buffer[0]=0; BEGIN(CONST_STRING);}
<CONST_STRING>[^\\\"]+ {strcat(buffer,yytext);}
<CONST_STRING>\\(\\[ntr]|" ")+ {strcat(buffer, "");}
<CONST_STRING>\\\\ {strcat(buffer, "\\");}
<CONST_STRING>\\n {strcat(buffer, "\n");}
<CONST_STRING>\\t {strcat(buffer, "\t");}
<CONST_STRING>\\0 {strcat(buffer, "\0");}
<CONST_STRING>\\r {strcat(buffer, "\r");}
<CONST_STRING>\\\" {strcat(buffer, "\"");}
<CONST_STRING>\" {printf("(%s) - Found CONST_STRING\n", buffer); BEGIN(INITIAL);}

\' {buffer[0]=0; BEGIN(CHAR);}
<CHAR>[^\\\']+ {strcat(buffer,yytext);}
<CHAR>\\(\\[ntr]|" ")+ {strcat(buffer, "");}
<CHAR>\\\\ {strcat(buffer, "\\");}
<CHAR>\\n {strcat(buffer, "\n");}
<CHAR>\\t {strcat(buffer, "\t");}
<CHAR>\\0 {strcat(buffer, "\0");}
<CHAR>\\r {strcat(buffer, "\r");}
<CHAR>\\\" {strcat(buffer, "\"");}
<CHAR>\' {
if(strlen(buffer)==1){
printf("(%s) - Found CHAR\n", buffer); BEGIN(INITIAL);
}else{
printf("(%s) - Found ERROR_CHAR\n", buffer); BEGIN(INITIAL);
}
}

\/\* {buffer[0]=0; BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^\*\/]+ {strcat(buffer,yytext);}
<MULTILINE_COMMENT>\* {strcat(buffer, "*");}
<MULTILINE_COMMENT>\/ {strcat(buffer, "/");}
<MULTILINE_COMMENT>\*\/ {printf("(%s) - Found MULTILINE_COMMENT\n", buffer); BEGIN(INITIAL);}

\/\/ {buffer[0]=0; BEGIN(ONELINE_COMMENT);}
<ONELINE_COMMENT>[^\n] {strcat(buffer, yytext);}
<ONELINE_COMMENT>\n {printf("(%s) - Found ONELINE_COMMENT\n", buffer); BEGIN(INITIAL);}
<ONELINE_COMMENT><<EOF>> {printf("(%s) - Found ONELINE_COMMENT\n", buffer); BEGIN(INITIAL);}


\+ { printf("(%s) - Found PLUS_OPERATOR\n", yytext); }
\- { printf("(%s) - Found MINUS_OPERATOR\n", yytext); }
\* { printf("(%s) - Found MUL_OPERATOR\n", yytext); }
\/ { printf("(%s) - Found DIV_OPERATOR\n", yytext); }
\<= { printf("(%s) - Found LESS_OR_EQUAL_OPERATOR\n", yytext); }
\>= { printf("(%s) - Found MORE_OR_EQUAL_OPERATOR\n", yytext); }
\< { printf("(%s) - Found LESS_OPERATOR\n", yytext); }
\> { printf("(%s) - Found MORE_OPERATOR\n", yytext); }
\!= { printf("(%s) - Found NOT_EQUAL_OPERATOR\n", yytext); }
= { printf("(%s) - Found ASSIGNMENT_OPERATOR\n", yytext); }

== { printf("(%s) - Found EQUAL_OPERATOR\n", yytext); }
\! { printf("(%s) - Found NOT_OPERATOR\n", yytext); }
\|\| { printf("(%s) - Found OR_OPERATOR\n", yytext); }
\&\& { printf("(%s) - Found AND_OPERATOR\n", yytext); }

\[ { printf("(%s) - Found SQUARE_BRACKET\n", yytext); }
\] { printf("(%s) - Found SQUARE_BRACKET\n", yytext); }
\( { printf("(%s) - Found ROUND_BRACKET\n", yytext); }
\) { printf("(%s) - Found ROUND_BRACKET\n", yytext); }
\{ { printf("(%s) - Found BRACE\n", yytext); }
\} { printf("(%s) - Found BRACE\n", yytext); }
\; { printf("(%s) - Found SEMICOLON\n", yytext); }
\, { printf("(%s) - Found COMMA\n", yytext); }
\: { printf("(%s) - Found COLON\n", yytext); }
\. { printf("(%s) - Found DOT\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("(%s) - Found IDENTIFIER\n", yytext); }

{DIGIT}+(_+{DIGIT}*)+ {
remove_underline();
printf("(%d) - Found DECIMAL_INTEGER\n", atoi(yytext));
}

0o(_*[0-7])+ {
remove_underline();
printf("(%d) - Found OCTAL_INTEGER\n", strtol(yytext+2, NULL, 8));
}

0x(_*[0-9A-Fa-f])+ {
remove_underline();
printf("(%d) - Found HEXADECIMAL_INTEGER\n", strtol(yytext+2, NULL, 16));
}

0b(_*[0-1])+ {
remove_underline();
printf("(%d) - Found BINARY_INTEGER\n", strtol(yytext+2, NULL, 2));
}

" " {}
\n {}

%%

int remove_char(char *s, int pos)
{
  int length = strlen(s);

  if (pos >= length) return 0;

  for (int i = pos; i < length; i++)
    s[i] = s[i + 1];

  return 1;
}

void remove_underline()
{
    char* ptr = strchr(yytext, '_');
    while (ptr != NULL){
        ptr = strchr(yytext, '_');
        int pos = ptr - yytext;
        remove_char(yytext, pos);
    }
}