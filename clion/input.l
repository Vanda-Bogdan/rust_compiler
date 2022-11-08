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
int remove_char(char *s, int pos);
void remove_underline();
void remove_f64();
void remove_i32();
int int_buffer;
char buf_char[2];
char buffer[1000];
%}

as { printf("(%s) - Found KW_AS\n", yytext);}
break { printf("(%s) - Found KW_BREAK\n", yytext); return BREAK;}
const { printf("(%s) - Found KW_CONST\n", yytext); return CONST;}
continue { printf("(%s) - Found KW_CONTINUE\n", yytext); return CONTINUE;}
crate { printf("(%s) - Found KW_CRATE\n", yytext); return CRATE;}
else { printf("(%s) - Found KW_ELSE\n", yytext); return ELSE;}
enum { printf("(%s) - Found KW_ENUM\n", yytext); return ENUM;}
extern { printf("(%s) - Found KW_EXTERN\n", yytext);}
fn { printf("(%s) - Found KW_FN\n", yytext); return FN;}
for { printf("(%s) - Found KW_FOR\n", yytext); return FOR;}
if { printf("(%s) - Found KW_IF\n", yytext); return IF;}
impl { printf("(%s) - Found KW_IMPL\n", yytext); return IMPL;}
in { printf("(%s) - Found KW_IN\n", yytext); return IN;}
let { printf("(%s) - Found KW_LET\n", yytext); return LET;}
loop { printf("(%s) - Found KW_LOOP\n", yytext); return LOOP;}
match { printf("(%s) - Found KW_MATCH\n", yytext);}
mod { printf("(%s) - Found KW_MOD\n", yytext);}
move { printf("(%s) - Found KW_MOVE\n", yytext);}
mut { printf("(%s) - Found KW_MUT\n", yytext); return MUT;}
pub { printf("(%s) - Found KW_PUB\n", yytext); return PUB;}
ref { printf("(%s) - Found KW_REF\n", yytext);}
return { printf("(%s) - Found KW_RETURN\n", yytext); return RETURN;}
self { printf("(%s) - Found KW_SELFVALUE\n", yytext); return SELF;}
static { printf("(%s) - Found KW_STATIC\n", yytext);}
struct { printf("(%s) - Found KW_STRUCT\n", yytext); return STRUCT;}
super { printf("(%s) - Found KW_SUPER\n", yytext); return SUPER;}
trait { printf("(%s) - Found KW_TRAIT\n", yytext); return TRAIT;}
type { printf("(%s) - Found KW_TYPE\n", yytext);}
unsafe { printf("(%s) - Found KW_UNSAFE\n", yytext);}
use { printf("(%s) - Found KW_USE\n", yytext);}
where { printf("(%s) - Found KW_WHERE\n", yytext);}
while { printf("(%s) - Found KW_WHILE\n", yytext); return WHILE;}
async { printf("(%s) - Found KW_ASYNC\n", yytext);}
await { printf("(%s) - Found KW_AWAITE\n", yytext);}
dyn { printf("(%s) - Found KW_DYN\n", yytext);}
String { printf("(%s) - Found KW_STRING\n", yytext);}
char { printf("(%s) - Found KW_CHAR\n", yytext); return CHAR;}
bool { printf("(%s) - Found KW_BOOLEAN\n", yytext); return BOOL;}

false { printf("(%s) - Found BOOLEAN_FALSE\n", yytext); return FALSE;}
true { printf("(%s) - Found BOOLEAN_TRUE\n", yytext); return TRUE;}

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
<CONST_STRING><<EOF>> {printf("(%s) - Error ERROR_STRING\n", buffer); BEGIN(INITIAL);}
<CONST_STRING>\\ {printf("(%s) - Error NOT_ESCAPED_SLASH\n", buffer); BEGIN(INITIAL);}
<CONST_STRING>\" {
printf("(%s) - Found CONST_STRING\n", buffer); BEGIN(INITIAL);
yylval.string_const=(char *)malloc(strlen(buffer)+1);
strcpy(yylval.string_const, buffer);
return STRING_LITERAL;
}

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
yylval.char_const=(char *)malloc(strlen(buffer)+1);
strcpy(yylval.char_const, buffer);
return CHAR_LITERAL;
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


\+ { printf("(%s) - Found PLUS_OPERATOR\n", yytext); return '+';}
\- { printf("(%s) - Found MINUS_OPERATOR\n", yytext); return '-';}
\* { printf("(%s) - Found MUL_OPERATOR\n", yytext); return '*';}
\/ { printf("(%s) - Found DIV_OPERATOR\n", yytext); return '/';}
\+\= { printf("(%s) - Found PLUS_ASSIGNMENT_OPERATOR\n", yytext);}
\-\= { printf("(%s) - Found MINUS_ASSIGNMENT_OPERATOR\n", yytext);}
\*\= { printf("(%s) - Found MUL_ASSIGNMENT_OPERATOR\n", yytext);}
\/\= { printf("(%s) - Found DIV_ASSIGNMENT_OPERATOR\n", yytext);}
\<= { printf("(%s) - Found LESS_OR_EQUAL_OPERATOR\n", yytext); return LESS_EQUAL;}
\>= { printf("(%s) - Found MORE_OR_EQUAL_OPERATOR\n", yytext); return GREATER_EQUAL;}
\< { printf("(%s) - Found LESS_OPERATOR\n", yytext); return '<';}
\> { printf("(%s) - Found MORE_OPERATOR\n", yytext); return '>';}
\!= { printf("(%s) - Found NOT_EQUAL_OPERATOR\n", yytext); return NOT_EQUAL;}
= { printf("(%s) - Found ASSIGNMENT_OPERATOR\n", yytext); return '=';}
\^ { printf("(%s) - Found CIRCUMFLEX\n", yytext);}


== { printf("(%s) - Found EQUAL_OPERATOR\n", yytext); return EQUAL;}
\! { printf("(%s) - Found NOT_OPERATOR\n", yytext); return '!';}
\|\| { printf("(%s) - Found OR_OPERATOR\n", yytext); return OR;}
\&\& { printf("(%s) - Found AND_OPERATOR\n", yytext); return AND;}

\.\. { printf("(%s) - Found RANGE_OPERATOR\n", yytext); return RANGE;}
\.\.\= { printf("(%s) - Found RANGE_EQUAL_OPERATOR\n", yytext); return RANGE_IN;}
\-\> { printf("(%s) - Found ARROW_OPERATOR\n", yytext); return RIGHT_ARROW;}

\[ { printf("(%s) - Found SQUARE_BRACKET\n", yytext); return '[';}
\] { printf("(%s) - Found SQUARE_BRACKET\n", yytext); return ']';}
\( { printf("(%s) - Found ROUND_BRACKET\n", yytext); return '(';}
\) { printf("(%s) - Found ROUND_BRACKET\n", yytext); return ')';}
\{ { printf("(%s) - Found BRACE\n", yytext); return '{';}
\} { printf("(%s) - Found BRACE\n", yytext); return '}';}
\; { printf("(%s) - Found SEMICOLON\n", yytext); return ';';}
\, { printf("(%s) - Found COMMA\n", yytext); return ',';}
\: { printf("(%s) - Found COLON\n", yytext); return ':';}
\. { printf("(%s) - Found DOT\n", yytext); return '.';}
\& { printf("(%s) - Found AMPERSAND\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* {
printf("(%s) - Found IDENTIFIER\n", yytext);
yylval.string_const=(char *)malloc(strlen(yytext)+1);
strcpy(yylval.string_const, yytext);
return ID;
}

{DIGIT}+(_+{DIGIT}*)*(i32)? {
strcpy(buffer, yytext);
remove_underline(buffer);
remove_i32(buffer);
printf("(%d) - Found DECIMAL_INTEGER\n", atoi(buffer));
yylval.int_const=atoi(buffer);
return INT_LITERAL;
}

([0-9]_*)+(\.([0-9]_*))?[Ee][+-]?([0-9]|_)*[0-9]([0-9]|_)*(f64)? {
strcpy(buffer, yytext);
remove_underline(buffer);
remove_f64(buffer);
printf("(%f) - Found FLOAT_CONST\n", atof(buffer));
yylval.float_const=atof(buffer);
return FLOAT_LITERAL;
}

([0-9]_*)+(f64|\.(([0-9]_*)+(f64)?)) {
strcpy(buffer, yytext);
remove_underline(buffer);
remove_f64(buffer);
printf("(%f) - Found FLOAT_CONST\n", atof(buffer));
yylval.float_const=atof(buffer);
return FLOAT_LITERAL;
}

0o(_*[0-7])+(i32)? {
strcpy(buffer, yytext);
remove_underline(buffer);
remove_i32(buffer);
printf("(%d) - Found OCTAL_INTEGER\n", strtol(buffer+2, NULL, 8));
yylval.float_const=strtol(buffer+2, NULL, 8);
return FLOAT_LITERAL;
}

0x(_*[0-9A-Fa-f])+(i32)? {
strcpy(buffer, yytext);
remove_underline(buffer);
remove_i32(buffer);
printf("(%d) - Found HEXADECIMAL_INTEGER\n", strtol(buffer+2, NULL, 16));
yylval.int_const=strtol(buffer+2, NULL, 16);
return INT_LITERAL;
}

0b(_*[0-1])+(i32)? {
strcpy(buffer, yytext);
remove_underline(buffer);
remove_i32(buffer);
printf("(%d) - Found BINARY_INTEGER\n", strtol(buffer+2, NULL, 2));
yylval.int_const=strtol(buffer+2, NULL, 2);
return INT_LITERAL;
}

[0-9]*[a-zA-Z_][a-zA-Z0-9_]* { printf("(%s) - Error IDENTIFIER\n", yytext); }

[[:space:]] {}

%%

int remove_char(char *s, int pos)
{
  int length = strlen(s);

  if (pos >= length) return 0;

  for (int i = pos; i < length; i++)
    s[i] = s[i + 1];

  return 1;
}

void remove_underline(char* buffer)
{
    char* ptr = strchr(buffer, '_');
    while (ptr != NULL){
        ptr = strchr(buffer, '_');
        int pos = ptr - buffer;
        remove_char(buffer, pos);
    }
}

void remove_f64(char* buffer)
{
    char* ptr = strstr(buffer, "f64");
    if (ptr != NULL){
        int pos = ptr - buffer;
        buffer[pos] = '\0';
    }
}

void remove_i32(char* buffer)
{
    char* ptr = strstr(buffer, "i32");
        if (ptr != NULL){
            int pos = ptr - buffer;
            buffer[pos] = '\0';
        }
}