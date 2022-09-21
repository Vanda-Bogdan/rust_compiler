%option noyywrap
%option never-interactive

NW [^A-Za-z_\d]

%x CONST_STRING
%x MULTILINE_COMMENT
%x ONELINE_COMMENT

%{
#include <stdio.h>
#include <string.h>
char buffer[1000];
%}

%%

{NW}[A-Za-z_][A-Za-z\d_]*{NW} { printf("%s - Found IDENTIFIER\n", yytext); }

as { printf("Found KW_AS"); }
break { printf("Found KW_BREAK"); }
const { printf("Found KW_CONST"); }
continue { printf("Found KW_CONTINUE"); }
crate { printf("Found KW_CRATE"); }
else { printf("Found KW_ELSE"); }
enum { printf("Found KW_ENUM"); }
extern { printf("Found KW_EXTERN"); }
false { printf("Found KW_FALSE"); }
fn { printf("Found KW_FN"); }
for { printf("Found KW_FOR"); }
if { printf("Found KW_IF"); }
impl { printf("Found KW_IMPL"); }
in { printf("Found KW_IN"); }
let { printf("Found KW_LET"); }
loop { printf("Found KW_LOOP"); }
match { printf("Found KW_MATCH"); }
mod { printf("Found KW_MOD"); }
move { printf("Found KW_MOVE"); }
mut { printf("Found KW_MUT"); }
pub { printf("Found KW_PUB"); }
ref { printf("Found KW_REF"); }
return { printf("Found KW_RETURN"); }
self { printf("Found KW_SELFVALUE"); }
Self { printf("Found KW_SELFTYPE"); }
static { printf("Found KW_STATIC"); }
struct { printf("Found KW_STRUCT"); }
super { printf("Found KW_SUPER"); }
trait { printf("Found KW_TRAIT"); }
true { printf("Found KW_TRUE"); }
type { printf("Found KW_TYPE"); }
unsafe { printf("Found KW_UNSAFE"); }
use { printf("Found KW_USE"); }
where { printf("Found KW_WHERE"); }
while { printf("Found KW_WHILE"); }
async { printf("Found KW_ASYNC"); }
await { printf("Found KW_AWAITE"); }
dyn { printf("Found KW_DYN"); }

\" {buffer[0]=0; BEGIN(CONST_STRING);}
<CONST_STRING>[^\\\"]+ {strcat(buffer,yytext);}
<CONST_STRING>\\(\\[ntbravf]|" ")+ {strcat(buffer, "");}
<CONST_STRING>\\\\ {strcat(buffer, "\\");}
<CONST_STRING>\\n {strcat(buffer, "\n");}
<CONST_STRING>\\t {strcat(buffer, "\t");}
<CONST_STRING>\\r {strcat(buffer, "\r");}
<CONST_STRING>\\\" {strcat(buffer, "\"");}
<CONST_STRING>\" {printf("Found CONST_STRING - %s", buffer); BEGIN(INITIAL);}

\/\* {buffer[0]=0; BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^\*\/]+ {strcat(buffer,yytext);}
<MULTILINE_COMMENT>\* {strcat(buffer, "*");}
<MULTILINE_COMMENT>\/ {strcat(buffer, "/");}
<MULTILINE_COMMENT>\*\/ {printf("Found MULTILINE_COMMENT - %s", buffer); BEGIN(INITIAL);}

\/\/ {buffer[0]=0; BEGIN(ONELINE_COMMENT);}
<ONELINE_COMMENT>[^\n] {strcat(buffer, yytext);}
<ONELINE_COMMENT>\n {printf("Found ONELINE_COMMENT - %s\n", buffer); BEGIN(INITIAL);}
<ONELINE_COMMENT><<EOF>> {printf("Found ONELINE_COMMENT - %s\n", buffer); BEGIN(INITIAL);}

\+ { printf("Found PLUS_OPERATOR - %s\n", yytext); }
\- { printf("Found MINUS_OPERATOR - %s\n", yytext); }
\* { printf("Found MUL_OPERATOR - %s\n", yytext); }
\/ { printf("Found DIV_OPERATOR - %s\n", yytext); }
\<= { printf("Found LESS_OR_EQUAL_OPERATOR - %s\n", yytext); }
\>= { printf("Found MORE_OR_EQUAL_OPERATOR - %s\n", yytext); }
\< { printf("Found LESS_OPERATOR - %s\n", yytext); }
\> { printf("Found MORE_OPERATOR - %s\n", yytext); }
\!= { printf("Found NOT_EQUAL_OPERATOR - %s\n", yytext); }
= { printf("Found ASSIGNMENT_OPERATOR - %s\n", yytext); }

== { printf("Found EQUAL_OPERATOR - %s\n", yytext); }
\! { printf("Found NOT_OPERATOR - %s\n", yytext); }
\|\| { printf("Found OR_OPERATOR - %s\n", yytext); }
\&\& { printf("Found AND_OPERATOR - %s\n", yytext); }

\[ { printf("Found SQUARE_BRACKET - %s\n", yytext); }
\] { printf("Found SQUARE_BRACKET - %s\n", yytext); }
\( { printf("Found ROUND_BRACKET - %s\n", yytext); }
\) { printf("Found ROUND_BRACKET - %s\n", yytext); }
\{ { printf("Found BRACE - %s\n", yytext); }
\} { printf("Found BRACE - %s\n", yytext); }
\; { printf("Found SEMICOLON - %s\n", yytext); }
\, { printf("Found COMMA - %s\n", yytext); }
\: { printf("Found COLON - %s\n", yytext); }



%%