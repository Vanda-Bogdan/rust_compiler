%token FOR LOOP IN IF ELSE WHILE LET MUT FN BREAK CONTINUE RETURN ENUM CONST STRUCT IMPL TRAIT PUB CRATE SELF SUPER
%token ID

%token INT_LITERAL TRUE FALSE STRING_LITERAL FLOAT_LITERAL CHAR_LITERAL
%token INT BOOL STRING FLOAT CHAR

%token ';' '(' '{' '}'
%token RANGE RANGE_IN // .. ..=
%token RIGHT_ARROW

%right '=' PLUS_ASGN MINUS_ASGN MUL_ASGN DIV_ASGN REM_ASGN // = += -= *= /= %=
%left AND OR
%left '<' '>' LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL     // <= >= == !=
%left '+' '-'
%left '*' '/'
%left '!' UMINUS
%nonassoc ')'


%{
#include tree_nodes.h
%}

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
                | ID
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
            ;

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
      ;

BlockExpr: '{' StmtList '}'
;

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
    | Visibility OtherStmt
    ;

ExprStmt: ExprWithoutBlock ';'
        | ExprWithBlock ';'
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
         | Trait
         | Impl
         ;

//----Enum----
Enum: ENUM ID '{' EnumItems '}'
    | ENUM ID '{' EnumItems ',' '}'
    ;

EnumItems: EnumItem
         | EnumItems ',' EnumItem
         ;

EnumItem: Visibility ID
        | ID
        | Visibility ID '=' Expr
        | ID '=' Expr
        | Visibility ID '=' '{' StructFields_final '}'
        | ID '=' '{' StructFields_final '}'
        ;

//----Function----
Function: FN ID '(' FuncParamList_final ')' FuncReturnType BlockExpr
        | FN ID '(' FuncParamList_final ')' FuncReturnType ';'
        | FN ID '(' FuncParamList_final ')' BlockExpr
        | FN ID '(' FuncParamList_final ')' ';'
        ;

FuncParamList_final: /*empty*/
                   | FuncParamList
                   | FuncParamList ','
                   ;

FuncParamList: FuncParam
             | FuncParamList ',' FuncParam
             ;

FuncParam: ID ':' Type
;

FuncReturnType: RIGHT_ARROW Type
;


//-----Pattern-----
/*Pattern: Literal
       | ID
       | '(' Pattern ')'
       | SlicePattern
       ;

SlicePattern: '[' SlicePatternList ']'
            | '[' SlicePatternList ',' ']'
            ;


SlicePatternList: Pattern
                | SlicePatternList ',' Pattern
                ;
*/

//-----Struct-----

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

StructField: Visibility ID ':' Type
           | ID ':' Type
           ;

//---------Implementation---------
Impl: InherentImpl
    | TraitImpl
    ;

InherentImpl: IMPL Type '{' AssociatedItems_final '}'
;

TraitImpl: IMPL ID FOR Type '{' AssociatedItems_final '}'
;

//-------------Trait-------------
Trait: TRAIT ID '{' AssociatedItems_final '}'
;

AssociatedItems_final: /*empty*/
                     | AssociatedItems
                     ;

AssociatedItems: AssociatedItem
               | AssociatedItems AssociatedItem
               ;

AssociatedItem: Visibility Function
              | Function
              | Visibility ConstantItem
              | ConstantItem
              ;

ConstantItem: CONST ID ':' Type ';'
            | CONST ID ':' Type '=' Expr ';'
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

//---------Visibility---------
Visibility: PUB
          | PUB '(' CRATE ')'
          | PUB '(' SELF ')'
          | PUB '(' SUPER ')'
          ;