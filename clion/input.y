%{

%}


%token FOR LOOP
%token IN
%token ID
%token IF ELSE
%token WHILE
%token LET MUT

%token INT_CONST BOOL_CONST STRING_CONST FLOAT_CONST CHAR_CONST
%token INT BOOL STRING FLOAT CHAR

%token ';' '('
%token '..' '..='

%right '=' '+=' '-=' '*=' '/='
%left '<' '>' '<=' '>=' '==' '!='
%left '+' '-'
%left '*' '/'
%left '!' UMINUS
%nonassoc ')'

%%

while_stmt: WHILE '(' expr ')' stmt_seq_e
          | WHILE expr stmt_seq_e
          ;

if_stmt: IF '(' expr ')' stmt_seq_e
       | IF expr stmt_seq_e
       | IF '(' expr ')' stmt_seq_e ELSE stmt_seq_e
       | IF expr stmt_seq_e ELSE stmt_seq_e
       ;

for_stmt: FOR ID IN expr stmt_seq_e
;

loop_stmt: LOOP stmt_seq_e
;

expr: INT_CONST
    | BOOL_CONST
    | STRING_CONST
    | FLOAT_CONST
    | CHAR_CONST
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '+=' expr
    | expr '-=' expr
    | expr '*=' expr
    | expr '/=' expr
    | expr '=' expr
    | expr '<' expr
    | expr '>' expr
    | expr '<=' expr
    | expr '>=' expr
    | expr '==' expr
    | expr '!=' expr
    | expr '&&' expr
    | expr '||' expr
    | '!' expr
    | '-' expr %prec UMINUS
    | ID
    | ID '(' expr_list_e ')'
    | '(' expr ')'
    ;

expr_list_e: /*empty*/
           | expr_list
           ;

expr_list: expr
         | expr_list ',' expr
         ;

stmt: expr ';'
    | '{' stmt_seq_e '}'
    | while_stmt
    | for_stmt
    | if_stmt
    | loop_stmt
    ;

stmt_seq: stmt
        | stmt_seq stmt
        ;

stmt_seq_e: /*empty*/
          | stmt_seq
          ;

var_declar: let ID ':' type ';'
          | let ID '=' expr ';'
          ;

let: LET MUT
   | LET
   ;

type: INT
    | STRING
    | CHAR
    | FLOAT
    | BOOL