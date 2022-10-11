%token FOR LOOP IN IF ELSE WHILE LET MUT FN
%token ID

%token INT_CONST BOOL_CONST STRING_CONST FLOAT_CONST CHAR_CONST
%token INT BOOL STRING FLOAT CHAR

%token ';' '(' '{' '}'
%token RL RIRL // .. ..=

%right '=' PLUS_ASGN MINUS_ASGN MUL_ASGN DIV_ASGN // = += -= *= /=
%left AND OR
%left '<' '>' L_EQ G_EQ EQ N_EQ                    // <= >= == !=
%left '+' '-'
%left '*' '/'
%left '!' UMINUS
%nonassoc ')'

%%

program : stmt_seq_e
;

while_stmt: WHILE '(' expr ')' '{' stmt_seq_e '}'
          | WHILE expr '{' stmt_seq_e '}'
          ;

if_stmt: IF '(' expr ')' '{' stmt_seq_e '}' //убрать, вернуть скобки в expr
       | IF expr '{' stmt_seq_e '}'
       | IF '(' expr ')' stmt_seq_e ELSE '{' stmt_seq_e '}'
       | IF expr stmt_seq_e ELSE '{' stmt_seq_e '}'
       ;

for_stmt: FOR ID IN expr '{' stmt_seq_e '}'
;

loop_stmt: LOOP '{' stmt_seq_e '}'
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
    | expr PLUS_ASGN expr
    | expr MINUS_ASGN expr
    | expr MUL_ASGN expr
    | expr DIV_ASGN expr
    | expr '=' expr
    | expr '<' expr
    | expr '>' expr
    | expr L_EQ expr
    | expr G_EQ expr
    | expr EQ expr
    | expr N_EQ expr
    | expr AND expr
    | expr OR expr
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
          | let ID '=' expr ';' // вариант указать тип (проверить возможность дефолтного значения)
          ;

func_declar: FN ID '(' declar_parameters_e ')' stmt_seq_e
;

declar_parameters_e: /*empty*/
                   | declar_parameters
                   ;

declar_parameters: declar_param
                 | declar_parameters ',' declar_param
                 ;

declar_param: ID ':' type
;

let: LET MUT
   | LET
   ;

type: INT
    | STRING
    | CHAR
    | FLOAT
    | BOOL
    ;