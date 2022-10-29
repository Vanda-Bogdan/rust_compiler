%token FOR LOOP IN IF ELSE WHILE LET MUT FN CONTINUE ENUM CONST STRUCT IMPL TRAIT PUB CRATE SELF SUPER
%token ID

%token INT_LITERAL TRUE FALSE STRING_LITERAL FLOAT_LITERAL CHAR_LITERAL
%token INT BOOL STRING FLOAT CHAR

%token ';' '(' '}' ']'
 // .. ..=
%token RIGHT_ARROW

%nonassoc RETURN BREAK
%nonassoc '.' '[' '{'        //todo О.А. ругался на это, забыл на че поменять
%right '='
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

ExprList: ExprWithBlock
        | ExprWithoutBlock
        | ExprList ',' ExprWithBlock
        | ExprList ',' ExprWithoutBlock
        ;

//------------------ExprWithoutBlock-------------------
ExprWithoutBlock: Literal
                | OperatorExpr
                | BREAK ExprWithBlock
                | BREAK ExprWithoutBlock
                | BREAK
                | CONTINUE
                | '(' ExprWithBlock ')'
                | '(' ExprWithoutBlock ')'
                | ArrayExpr
                | ExprWithBlock '[' ExprWithBlock ']'                    //Index
                | ExprWithoutBlock '[' ExprWithBlock ']'
                | ExprWithBlock '[' ExprWithoutBlock ']'
                | ExprWithoutBlock '[' ExprWithoutBlock ']'
                | ID '(' ExprList_final ')'            //Call function
                | ExprWithBlock '.' ID '(' ExprList_final ')'   //Call method
                | ExprWithoutBlock '.' ID '(' ExprList_final ')'
                | ExprWithBlock '.' ID                          //Field access
                | ExprWithoutBlock '.' ID
                | RangeExpr
                | RETURN ExprWithBlock
                | RETURN ExprWithoutBlock
                | RETURN
                | ID
                ;

Literal: CHAR_LITERAL
       | STRING_LITERAL
       | INT_LITERAL
       | FLOAT_LITERAL
       | TRUE
       | FALSE
       ;

OperatorExpr: ExprWithoutBlock '+' ExprWithoutBlock                         //Arithmetic
            | ExprWithBlock '+' ExprWithoutBlock
            | ExprWithoutBlock '+' ExprWithBlock
            | ExprWithBlock '+' ExprWithBlock
            | ExprWithoutBlock '-' ExprWithoutBlock
            | ExprWithBlock '-' ExprWithoutBlock
            | ExprWithoutBlock '-' ExprWithBlock
            | ExprWithBlock '-' ExprWithBlock
            | ExprWithoutBlock '*' ExprWithoutBlock
            | ExprWithBlock '*' ExprWithoutBlock
            | ExprWithoutBlock '*' ExprWithBlock
            | ExprWithBlock '*' ExprWithBlock
            | ExprWithoutBlock '/' ExprWithoutBlock
            | ExprWithBlock '/' ExprWithoutBlock
            | ExprWithoutBlock '/' ExprWithBlock
            | ExprWithBlock '/' ExprWithBlock
            | ExprWithoutBlock EQUAL ExprWithoutBlock                        //Comparison
            | ExprWithoutBlock EQUAL ExprWithBlock
            | ExprWithBlock EQUAL ExprWithoutBlock
            | ExprWithBlock EQUAL ExprWithBlock
            | ExprWithoutBlock NOT_EQUAL ExprWithoutBlock
            | ExprWithoutBlock NOT_EQUAL ExprWithBlock
            | ExprWithBlock NOT_EQUAL ExprWithoutBlock
            | ExprWithBlock NOT_EQUAL ExprWithBlock
            | ExprWithoutBlock '>' ExprWithoutBlock
            | ExprWithoutBlock '>' ExprWithBlock
            | ExprWithBlock '>' ExprWithoutBlock
            | ExprWithBlock '>' ExprWithBlock
            | ExprWithoutBlock '<' ExprWithoutBlock
            | ExprWithoutBlock '<' ExprWithBlock
            | ExprWithBlock '<' ExprWithoutBlock
            | ExprWithBlock '<' ExprWithBlock
            | ExprWithoutBlock GREATER_EQUAL ExprWithoutBlock
            | ExprWithoutBlock GREATER_EQUAL ExprWithBlock
            | ExprWithBlock GREATER_EQUAL ExprWithoutBlock
            | ExprWithBlock GREATER_EQUAL ExprWithBlock
            | ExprWithoutBlock LESS_EQUAL ExprWithoutBlock
            | ExprWithoutBlock LESS_EQUAL ExprWithBlock
            | ExprWithBlock LESS_EQUAL ExprWithoutBlock
            | ExprWithBlock LESS_EQUAL ExprWithBlock
            | ExprWithBlock '?'                               //ErrorPropagation
            | ExprWithoutBlock '?'
            | '-' ExprWithBlock %prec UMINUS                  //Negation
            | '-' ExprWithoutBlock %prec UMINUS
            | '!' ExprWithBlock
            | '!' ExprWithoutBlock
            | ExprWithBlock OR ExprWithBlock                               //Boolean
            | ExprWithoutBlock OR ExprWithBlock
            | ExprWithBlock OR ExprWithoutBlock
            | ExprWithoutBlock OR ExprWithoutBlock
            | ExprWithBlock AND ExprWithBlock
            | ExprWithoutBlock AND ExprWithBlock
            | ExprWithBlock AND ExprWithoutBlock
            | ExprWithoutBlock AND ExprWithoutBlock
            | ExprWithBlock '=' ExprWithBlock                             //Assignment
            | ExprWithoutBlock '=' ExprWithBlock
            | ExprWithBlock '=' ExprWithoutBlock
            | ExprWithoutBlock '=' ExprWithoutBlock
            ;

ArrayExpr: '[' ExprList_final ']'
         | '[' ExprWithBlock ';' ExprWithBlock ']'
         | '[' ExprWithoutBlock ';' ExprWithBlock ']'
         | '[' ExprWithBlock ';' ExprWithoutBlock ']'
         | '[' ExprWithoutBlock ';' ExprWithoutBlock ']'
         ;

RangeExpr: ExprWithBlock RANGE ExprWithBlock
         | ExprWithoutBlock RANGE ExprWithBlock
         | ExprWithBlock RANGE ExprWithoutBlock
         | ExprWithoutBlock RANGE ExprWithoutBlock
         | ExprWithBlock RANGE
         | ExprWithoutBlock RANGE
         | RANGE ExprWithBlock
         | RANGE ExprWithoutBlock
         | RANGE
         | ExprWithBlock RANGE_IN ExprWithBlock
         | ExprWithoutBlock RANGE_IN ExprWithBlock
         | ExprWithBlock RANGE_IN ExprWithoutBlock
         | ExprWithoutBlock RANGE_IN ExprWithoutBlock
         | RANGE_IN ExprWithBlock
         | RANGE_IN ExprWithoutBlock
         ;

//------------------ExprWithBlock-------------------
ExprWithBlock: IfExpr
             | LoopExpr
             | WhileExpr
             | ForExpr
             ;

LoopExpr: LOOP BlockExpr
;

WhileExpr: WHILE ExprWithBlock BlockExpr
         | WHILE ExprWithoutBlock BlockExpr
         ;

ForExpr: FOR ID IN ExprWithBlock BlockExpr
       | FOR ID IN ExprWithoutBlock BlockExpr
       ;

IfExpr: IF ExprWithBlock BlockExpr
      | IF ExprWithoutBlock BlockExpr
      | IF ExprWithBlock BlockExpr ELSE BlockExpr
      | IF ExprWithoutBlock BlockExpr ELSE BlockExpr
      ;

BlockExpr: '{' StmtList '}'
         | '{' '}'
         ;

//--------------------Statement---------------------

StmtList: Stmt
        | StmtList Stmt
        ;

Stmt: ';'
    | ExprWithoutBlock ';'
    | ExprWithBlock ';'              //todo убрал правило Stmt->ExprWithBlock т.к. вызвало конфликт с этой строчкой, можно вернуть если поймем как решить
    | LetStmt
    | OtherStmt
    | Visibility OtherStmt
    ;


LetStmt: LET ID ':' Type '=' ExprWithBlock ';'
       | LET ID ':' Type '=' ExprWithoutBlock ';'
       | LET ID '=' ExprWithBlock ';'
       | LET ID '=' ExprWithoutBlock ';'
       | LET MUT ID ':' Type '=' ExprWithBlock ';'
       | LET MUT ID ':' Type '=' ExprWithoutBlock ';'
       | LET MUT ID '=' ExprWithBlock ';'
       | LET MUT ID '=' ExprWithoutBlock ';'
       | LET MUT ID ':' Type ';'
       | LET MUT ID ';'
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
        | Visibility ID '=' ExprWithBlock
        | Visibility ID '=' ExprWithoutBlock
        | ID '=' ExprWithBlock
        | ID '=' ExprWithoutBlock
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
         | MUT ID ':' Type
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
            | CONST ID ':' Type '=' ExprWithBlock ';'
            | CONST ID ':' Type '=' ExprWithoutBlock ';'
            ;

//---------ConstStatement---------
ConstStmt: CONST ID ':' Type ';'
         | CONST ID ':' Type '=' ExprWithBlock ';'
         | CONST ID ':' Type '=' ExprWithoutBlock ';'
         ;

//---------Type---------
Type: INT
    | STRING
    | CHAR
    | FLOAT
    | BOOL
    | ID
    ;

//---------Visibility---------
Visibility: PUB
          | PUB '(' CRATE ')'
          | PUB '(' SELF ')'
          | PUB '(' SUPER ')'
          ;