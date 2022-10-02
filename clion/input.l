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
#include <stdlib.h>
%}

%%

%{
char buffer[1000];
int remove_char(char *s, int pos);
void remove_underline();
void remove_f64();
void remove_i32();
int int_buffer;
char buf_char[2];
%}


as { printf("(%s) - Found KW_AS\n", yytext); }
break { printf("(%s) - Found KW_BREAK\n", yytext); }
const { printf("(%s) - Found KW_CONST\n", yytext); }
continue { printf("(%s) - Found KW_CONTINUE\n", yytext); }
crate { printf("(%s) - Found KW_CRATE\n", yytext); }
else { printf("(%s) - Found KW_ELSE\n", yytext); }
enum { printf("(%s) - Found KW_ENUM\n", yytext); }
extern { printf("(%s) - Found KW_EXTERN\n", yytext); }
fn { printf("(%s) - Found KW_FN\n", yytext); }
for { printf("(%s) - Found KW_FOR\n", yytext); }
f64 { printf("(%s) - Found KW_FLOAT64\n", yytext); }
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

false { printf("(%s) - Found BOOLEAN_FALSE\n", yytext); }
true { printf("(%s) - Found BOOLEAN_TRUE\n", yytext); }

\" {buffer[0]=0; BEGIN(CONST_STRING);}
<CONST_STRING>[^\\\"]+ {strcat(buffer,yytext);}
<CONST_STRING>\\\n[\n\t\r ]* {strcat(buffer, "");}
<CONST_STRING>\\\\ {strcat(buffer, "\\");}
<CONST_STRING>\\n {strcat(buffer, "\n");}
<CONST_STRING>\\t {strcat(buffer, "\t");}
<CONST_STRING>\\0 {strcat(buffer, "\0");}
<CONST_STRING>\\r {strcat(buffer, "\r");}
<CONST_STRING>\\\" {strcat(buffer, "\"");}
<CONST_STRING>\\\' {strcat(buffer, "\'");}
<CONST_STRING>\\x[0-7][0-9A-Fa-f] { buf_char[0] = strtol(yytext+2, NULL, 16); buf_char[1] = 0; strcat(buffer, buf_char);}
<CONST_STRING><<EOF>> {printf("(%s) - Found ERROR_STRING\n", buffer); BEGIN(INITIAL);}
<CONST_STRING>\\ {printf("(%s) - Found NOT_ESCAPED_SLASH\n", buffer); BEGIN(INITIAL);}
<CONST_STRING>\" {printf("(%s) - Found CONST_STRING\n", buffer); BEGIN(INITIAL);}

\' {buffer[0]=0; BEGIN(CHAR);}
<CHAR>\\x[0-7][0-9A-Fa-f]\' { yytext[strlen(yytext)-1] = '\0'; buf_char[0] = strtol(yytext+2, NULL, 16); printf( "(%c) - Found CHAR\n", buf_char[0] ); BEGIN(INITIAL);}
<CHAR>[^\\\']+ {strcat(buffer,yytext);}
<CHAR>\\\\ {strcat(buffer, "\\");}
<CHAR>\\n {strcat(buffer, "\n");}
<CHAR>\\t {strcat(buffer, "\t");}
<CHAR>\\0 {strcat(buffer, "\0");}
<CHAR>\\r {strcat(buffer, "\r");}
<CHAR>\\\" {strcat(buffer, "\"");}
<CHAR>\\\' {strcat(buffer, "\'");}
<CHAR><<EOF>> {printf("(%s) - Error CHAR\n", buffer); BEGIN(INITIAL);}
<CHAR>\' {
if(strlen(buffer)==1){
printf("(%s) - Found CHAR\n", buffer); BEGIN(INITIAL);
}else{
printf("(%s) - Error CHAR\n", buffer); BEGIN(INITIAL);
}
}

\/\* {buffer[0]=0; BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^\*\/]+ {strcat(buffer,yytext);}
<MULTILINE_COMMENT>\* {strcat(buffer, "*");}
<MULTILINE_COMMENT>\/ {strcat(buffer, "/");}
<MULTILINE_COMMENT><<EOF>> { printf("(%s) - Error COMMENT\n", buffer); BEGIN(INITIAL);}
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

\.\. { printf("(%s) - Found RANGE_OPERATOR\n", yytext); }
\.\.\= { printf("(%s) - Found RANGE_EQUAL_OPERATOR\n", yytext); }
\-\> { printf("(%s) - Found ARROW_OPERATOR\n", yytext); }

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
\& { printf("(%s) - Found AMPERSAND\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("(%s) - Found IDENTIFIER\n", yytext); }

{DIGIT}+(_+{DIGIT}*)*(i32)? {
remove_underline();
remove_i32();
printf("(%d) - Found DECIMAL_INTEGER\n", atoi(yytext));
}

([0-9]_*)+(\.([0-9]_*))?[Ee][+-]?([0-9]|_)*[0-9]([0-9]|_)*(f64)? {
remove_f64();
remove_underline();
printf("(%f) - Found FLOAT_CONST\n", atof(yytext));
}

([0-9]_*)+(f64|\.(([0-9]_*)+(f64)?)) {
remove_f64();
remove_underline();
printf("(%f) - Found FLOAT_CONST\n", atof(yytext));
}

0o(_*[0-7])+(i32)? {
remove_underline();
remove_i32();
printf("(%d) - Found OCTAL_INTEGER\n", strtol(yytext+2, NULL, 8));
}

0x(_*[0-9A-Fa-f])+(i32)? {
remove_underline();
remove_i32();
printf("(%d) - Found HEXADECIMAL_INTEGER\n", strtol(yytext+2, NULL, 16));
}

0b(_*[0-1])+(i32)? {
remove_underline();
remove_i32();
printf("(%d) - Found BINARY_INTEGER\n", strtol(yytext+2, NULL, 2));
}

[0-9]*[a-zA-Z_][a-zA-Z0-9_]* { printf("(%s) - Error IDENTIFIER\n", yytext); }

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

void remove_f64()
{
    char* ptr = strstr(yytext, "f64");
    if (ptr != NULL){
        int pos = ptr - yytext;
        yytext[pos] = '\0';
    }
}

void remove_i32()
{
    char* ptr = strstr(yytext, "i32");
        if (ptr != NULL){
            int pos = ptr - yytext;
            yytext[pos] = '\0';
        }
}