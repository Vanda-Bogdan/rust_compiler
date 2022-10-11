%token FOR LOOP IN IF ELSE WHILE LET MUT FN
%token ID

%token INT_CONST BOOL_CONST STRING_CONST FLOAT_CONST CHAR_CONST
%token INT BOOL STRING FLOAT CHAR

%token ';' '(' '{' '}'
%token RANGE RANGE_IN // .. ..=
%token RIGHT_ARROW

%right '=' PLUS_ASGN MINUS_ASGN MUL_ASGN DIV_ASGN REM_ASGN// = += -= *= /= %=
%left AND OR
%left '<' '>' LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL     // <= >= == !=
%left '+' '-'
%left '*' '/'
%left '!' UMINUS
%nonassoc ')'

%%

Program: Function
;

//--------------------Expressions---------------------


ExprList_final: /*empty*/
              | ExprList ','
              | ExprList
              ;

ExprList: Expr
        | ExprList ',' Expr
        ;

Expr : ExprWithoutBlock
     | ExprWithBlock
     ;

//--------------------ExprWithoutBlock---------------------
ExprWithoutBlock: Literal
                | OperatorExpr
                | BREAK Expr
                | CONTINUE
                | '(' Expr ')'
                | ArrayExpr
                | Expr '[' Expr ']'                     //Index
                | Expr '(' ExprList_final ')'           //Call function
                | Expr '.' ID '(' ExprList_final ')'    //Call method
                | Expr '.' ID                           //Field access
                | RangeExpr
                | ReturnExpr
                ;

Literal: CHAR_LITERAL
           | STRING_LITERAL
           | INT_LITERAL
           | FLOAT_LITERAL
           | TRUE
           | FALSE
           ;

OperatorExpr: Expr '+' Expr             //Arithmetic
            | Expr '-' Expr
            | Expr '*' Expr
            | Expr '/' Expr
            | Expr '%' Expr
            | Expr EQUAL Expr           //Comparison
            | Expr NOT_EQUAL Expr
            | Expr '>' Expr
            | Expr '<' Expr
            | Expr GREATER_EQUAL Expr
            | Expr LESS_EQUAL Expr
            | Expr '?'                  //ErrorPropagation
            | '-' Expr %prec UMINUS     //Negation
            | '!' Expr
            | Expr OR Expr              //Boolean
            | Expr AND Expr
            | Expr '=' Expr             //Assignment
            | Expr PLUS_ASGN Expr
            | Expr MINUS_ASGN Expr
            | Expr MUL_ASGN Expr
            | Expr DIV_ASGN Expr
            | Expr REM_ASGN Expr

ArrayExpr: '[' ExprList_final ']'       //Внутри скобок может быть пусто??
         | '[' Expr ';' Expr ']'
         ;

RangeExpr: Expr RANGE Expr
         | Expr RANGE
         | RANGE Expr
         | RANGE
         | Expr RANGE_IN Expr
         | RANGE_IN Expr
         ;

ReturnExpr: RETURN Expr
          | RETURN
          ;

//--------------------ExprWithBlock---------------------
ExprWithBlock: BlockExpr
             | LoopExpr
             | WhileExpr
             | ForExpr
             | IfExpr
             ;

LoopExpr: LOOP BlockExpr
;

WhileExpr: WHILE Expr BlockExpr
;

ForExpr: FOR ID IN Expr BlockExpr
;

IfExpr: IF Expr BlockExpr
      | IF Expr BlockExpr ELSE BlockExpr

BlockExpr: '{' StmtList '}'


//--------------------Statement---------------------

StmtList: Stmt
        | ExprWithoutBlock
        | StmtList Stmt
        | StmtList ExprWithoutBlock
        ;

Stmt: ';'
    | ExprStmt
    | LetStmt
    | OtherStmt
    ;

ExprStmt: ExprWithoutBlock ';'
        | ExprWithBlock
        ;

LetStmt: LET ID ':' Type '=' Expr ';'
       | LET ID '=' Expr ';'
       | LET ID ':' Type ';'
       | LET ID ';'
       ;

//---------OtherStatement---------
OtherStmt: Enum
         | Function
         | ConstStmt
         | Struct
         ;
// ДОБВАИТЬ СЮДА ЕЩЕ??????


//----Enum----
Enum: ENUM ID '{' EnumItems '}'
    | ENUM ID '{' EnumItems ',' '}'
    ;

EnumItems: EnumItem
         | EnumItems ',' EnumItem
         ;

EnumItem: ID
;

//----Function----
Function: fn ID '(' FuncParamList ')' FuncReturnType BlockExpr
        | fn ID '(' FuncParamList ')' FuncReturnType ';'
        | fn ID '(' FuncParamList ')' BlockExpr
        | fn ID '(' FuncParamList ')' ';'
        ;

FuncParamList_final: /*empty*/
                   | FuncParamList
                   | FuncParamList ','
                   ;

FuncParamList: FuncParam
             | FuncParamList ',' FuncParam
             ;

FuncParam: Pattern ':' Type
;

FuncReturnType: RIGHT_ARROW Type
;


//----Pattern----
Pattern: Literal
       | ID
       | '(' Pattern ')'
       | SlicePattern
       ;

SlicePattern: SlicePatternList
            | SlicePatternList ','
            ;

SlicePatternList: Pattern
                | SlicePatternList ',' Pattern
                ;

//----Struct----

Struct: STRUCT ID '{' StructFields_final '}'
      | STRUCT ID ';'
      ;

StructFields_final: /*empty*/
                  | StructFields
                  | StructFields ','
                  ;

StructFields: StructField
            | StructFields ',' StructField
            ;

StructField: ID ':' Type
;


//---------ConstStatement---------
ConstStmt: CONST ID ':' Type ';'
         | CONST ID ':' Type '=' Expr ';'
         ;


//---------Type---------
Type: INT
    | STRING
    | CHAR
    | FLOAT
    | BOOL
    ;