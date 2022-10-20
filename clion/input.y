%token FOR LOOP IN IF ELSE WHILE LET MUT FN CONTINUE ENUM CONST STRUCT IMPL TRAIT PUB CRATE SELF SUPER
%token ID

%token INT_LITERAL TRUE FALSE STRING_LITERAL FLOAT_LITERAL CHAR_LITERAL
%token INT BOOL STRING FLOAT CHAR

%token ';' '(' '}' ']'
 // .. ..=
%token RIGHT_ARROW

%nonassoc RETURN BREAK
%nonassoc '.' '[' '{'
%right '=' PLUS_ASGN MINUS_ASGN MUL_ASGN DIV_ASGN REM_ASGN // = += -= *= /= %=
%nonassoc RANGE RANGE_IN
%left AND OR
%left '<' '>' LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL     // <= >= == !=
%left '+' '-'
%left '*' '/' '%'
%left '!' UMINUS
%nonassoc '?'
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

Expr: Literal       { $$ = $1}
    | OperatorExpr  {}
    | BREAK
    | CONTINUE
    | '(' Expr ')'
    | ArrayExpr
    | Expr '[' Expr ']' {$$ = ExprFromIndex($1,$3)}                    //Index
    | ID '(' ExprList_final ')'           //Call function
    | Expr '.' ID '(' ExprList_final ')'    //Call method
    | Expr '.' ID                           //Field access
    | RangeExpr
    | ReturnExpr
    | ID
    ;

Literal: CHAR_LITERAL       { $$ = ExprFromCharLiteral($1); }
       | STRING_LITERAL     { $$ = ExprFromStringLiteral($1); }
       | INT_LITERAL        { $$ = ExprFromIntLiteral($1); }
       | FLOAT_LITERAL      { $$ = ExprFromFloatLiteral($1); }
       | TRUE               { $$ = ExprFromTrue($1); }
       | FALSE              { $$ = ExprFromFalse($1); }
       ;

OperatorExpr: Expr '+' Expr                         { $$ = createExpr(global_id, plus, $1, $3) }            //Arithmetic
            | Expr '-' Expr                         { $$ = createExpr(global_id, minus, $1, $3) }
            | Expr '*' Expr                         { $$ = createExpr(global_id, mul, $1, $3) }
            | Expr '/' Expr                         { $$ = createExpr(global_id, div, $1, $3) }
            | Expr '%' Expr                         { $$ = createExpr(global_id, rem, $1, $3) }
            | Expr EQUAL Expr                       { $$ = createExpr(global_id, equal, $1, $3) }           //Comparison
            | Expr NOT_EQUAL Expr                   { $$ = createExpr(global_id, not_equal, $1, $3) }
            | Expr '>' Expr                         { $$ = createExpr(global_id, greater, $1, $3) }
            | Expr '<' Expr                         { $$ = createExpr(global_id, less, $1, $3) }
            | Expr GREATER_EQUAL Expr               { $$ = createExpr(global_id, greater_equal, $1, $3) }
            | Expr LESS_EQUAL Expr                  { $$ = createExpr(global_id, less_equal, $1, $3) }
            | Expr '?'                              { $$ = createExpr(global_id, qt, $1, 0) }        //ErrorPropagation
            | '-' Expr %prec UMINUS                 { $$ = createExpr(global_id, uminus, 0, $2) }    //Negation
            | '!' Expr                              { $$ = createExpr(global_id, neg, 0, $2) }
            | Expr OR Expr                          { $$ = createExpr(global_id, or, $1, $3) }           //Boolean
            | Expr AND Expr                         { $$ = createExpr(global_id, and, $1, $3) }
            | Expr '=' Expr                         { $$ = createExpr(global_id, asgn, $1, $3) }        //Assignment
            | Expr PLUS_ASGN Expr                   { $$ = createExpr(global_id, plus_asgn, $1, $3) }
            | Expr MINUS_ASGN Expr                  { $$ = createExpr(global_id, minus_asgn, $1, $3) }
            | Expr MUL_ASGN Expr                    { $$ = createExpr(global_id, mul_asgn, $1, $3) }
            | Expr DIV_ASGN Expr                    { $$ = createExpr(global_id, div_asgn, $1, $3) }
            | Expr REM_ASGN Expr                    { $$ = createExpr(global_id, rem_asgn, $1, $3) }
            ;

ArrayExpr: '[' ExprList_final ']'
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

StmtWithBlock: IfStmt
             | LoopStmt
             | WhileStmt
             | ForStmt
             ;

LoopStmt: LOOP BlockExpr
;

WhileStmt: WHILE Expr BlockExpr
;

ForStmt: FOR ID IN Expr BlockExpr
;

IfStmt: IF Expr BlockExpr
      | IF Expr BlockExpr ELSE BlockExpr
      ;

BlockExpr: '{' StmtList '}'
         | '{' '}'
         ;

//--------------------Statement---------------------

StmtList: Stmt
        | StmtList Stmt
        ;

Stmt: ';'
    | Expr ';'
    | StmtWithBlock
    | LetStmt
    | OtherStmt
    | Visibility OtherStmt
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