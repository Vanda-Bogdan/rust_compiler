%{
#include <stdio.h>
#include "nodes.h"
#include "function.c"
#include "tree_print.h"
void yyerror(char const *s);
extern int yylex(void);
%}

%union {
	struct program_node * prg;
	struct expr_node * expr;
	struct expr_list_node * expr_list;
	struct stmt_node * stmt_;
	struct stmt_list_node * stmt_list;
	struct let_stmt_node * let_stmt;
	struct decl_stmt_node * decl_stmt;
	struct struct_item_node * struct_item;
	struct struct_node * struct_;
	struct struct_list_node * struct_items;
	struct enum_node * enum_;
	struct enum_item_node * enum_item;
	struct enum_list_node * enum_items;
	struct function_param_node * function_param;
	struct function_node * function_;
	struct function_params_node * function_params;
	struct const_stmt_node * const_stmt;
	struct associated_item_node * associated_item;
	struct trait_node * trait_;
	struct associated_items_node * associated_items;
	struct impl_node * impl_;
	int int_const;
	char * string_const;
	bool bool_const;
	float float_const;
	char char_const;
	enum visibility vis;
	enum type typ;
}

%token FOR LOOP IN IF ELSE WHILE LET MUT FN CONTINUE ENUM CONST STRUCT IMPL TRAIT PUB CRATE SELF SUPER
%token ID

%token INT_LITERAL TRUE FALSE STRING_LITERAL FLOAT_LITERAL CHAR_LITERAL
%token INT BOOL STRING FLOAT CHAR

%token ';' '(' '}' ']'
 // .. ..=
%token RIGHT_ARROW

%nonassoc RETURN BREAK
%nonassoc '{'
%right '='
%nonassoc RANGE RANGE_IN
%left AND OR
%left '<' '>' LESS_EQUAL GREATER_EQUAL EQUAL NOT_EQUAL     // <= >= == !=
%left '+' '-'
%left '*' '/'
%left '!' UMINUS
%nonassoc '?'
%left '.' '['
%nonassoc ')'

%%
Program: Function							{ $$ = ProgramCreate($1); }
;

//--------------------Expressions---------------------


ExprList_final: /*empty*/						{ $$ = ExprListFinal(0); }
              | ExprList ','						{ $$ = ExprListFinal($1); }
              | ExprList						{ $$ = ExprListFinal($1); }
              ;

ExprList: ExprWithBlock							{ $$ = ExprList($1); }
        | ExprWithoutBlock						{ $$ = ExprList($1); }
        | ExprList ',' ExprWithBlock					{ $$ = ExprListAdd($1, $3); }
        | ExprList ',' ExprWithoutBlock					{ $$ = ExprListAdd($1, $3); }
        ;

//------------------ExprWithoutBlock-------------------
ExprWithoutBlock: CHAR_LITERAL      					{ $$ = ExprFromCharLiteral($1); }
                | STRING_LITERAL	   				{ $$ = ExprFromStringLiteral($1); }
                | INT_LITERAL						{ $$ = ExprFromIntLiteral($1); }
                | FLOAT_LITERAL						{ $$ = ExprFromFloatLiteral($1); }
                | TRUE							{ $$ = ExprFromBoolLiteral($1); }
                | FALSE							{ $$ = ExprFromBoolLiteral($1); }
                | ExprWithoutBlock '+' ExprWithoutBlock			{ $$ = OperatorExpr(plus, $1, $3); }
                | ExprWithBlock '+' ExprWithoutBlock			{ $$ = OperatorExpr(plus, $1, $3); }
                | ExprWithoutBlock '+' ExprWithBlock			{ $$ = OperatorExpr(plus, $1, $3); }
                | ExprWithBlock '+' ExprWithBlock			{ $$ = OperatorExpr(plus, $1, $3); }
                | ExprWithoutBlock '-' ExprWithoutBlock			{ $$ = OperatorExpr(minus, $1, $3); }
                | ExprWithBlock '-' ExprWithoutBlock			{ $$ = OperatorExpr(minus, $1, $3); }
                | ExprWithoutBlock '-' ExprWithBlock			{ $$ = OperatorExpr(minus, $1, $3); }
                | ExprWithBlock '-' ExprWithBlock			{ $$ = OperatorExpr(minus, $1, $3); }
                | ExprWithoutBlock '*' ExprWithoutBlock			{ $$ = OperatorExpr(mul, $1, $3); }
                | ExprWithBlock '*' ExprWithoutBlock			{ $$ = OperatorExpr(mul, $1, $3); }
                | ExprWithoutBlock '*' ExprWithBlock			{ $$ = OperatorExpr(mul, $1, $3); }
                | ExprWithBlock '*' ExprWithBlock			{ $$ = OperatorExpr(mul, $1, $3); }
                | ExprWithoutBlock '/' ExprWithoutBlock			{ $$ = OperatorExpr(div_expr, $1, $3); }
                | ExprWithBlock '/' ExprWithoutBlock			{ $$ = OperatorExpr(div_expr, $1, $3); }
                | ExprWithoutBlock '/' ExprWithBlock			{ $$ = OperatorExpr(div_expr, $1, $3); }
                | ExprWithBlock '/' ExprWithBlock			{ $$ = OperatorExpr(div_expr, $1, $3); }
                | ExprWithoutBlock EQUAL ExprWithoutBlock		{ $$ = OperatorExpr(equal, $1, $3); }
                | ExprWithoutBlock EQUAL ExprWithBlock			{ $$ = OperatorExpr(equal, $1, $3); }
                | ExprWithBlock EQUAL ExprWithoutBlock			{ $$ = OperatorExpr(equal, $1, $3); }
                | ExprWithBlock EQUAL ExprWithBlock			{ $$ = OperatorExpr(equal, $1, $3); }
                | ExprWithoutBlock NOT_EQUAL ExprWithoutBlock		{ $$ = OperatorExpr(not_equal, $1, $3); }
                | ExprWithoutBlock NOT_EQUAL ExprWithBlock		{ $$ = OperatorExpr(not_equal, $1, $3); }
                | ExprWithBlock NOT_EQUAL ExprWithoutBlock		{ $$ = OperatorExpr(not_equal, $1, $3); }
                | ExprWithBlock NOT_EQUAL ExprWithBlock			{ $$ = OperatorExpr(not_equal, $1, $3); }
                | ExprWithoutBlock '>' ExprWithoutBlock			{ $$ = OperatorExpr(greater, $1, $3); }
                | ExprWithoutBlock '>' ExprWithBlock			{ $$ = OperatorExpr(greater, $1, $3); }
                | ExprWithBlock '>' ExprWithoutBlock			{ $$ = OperatorExpr(greater, $1, $3); }
                | ExprWithBlock '>' ExprWithBlock			{ $$ = OperatorExpr(greater, $1, $3); }
                | ExprWithoutBlock '<' ExprWithoutBlock			{ $$ = OperatorExpr(less, $1, $3); }
                | ExprWithoutBlock '<' ExprWithBlock			{ $$ = OperatorExpr(less, $1, $3); }
                | ExprWithBlock '<' ExprWithoutBlock			{ $$ = OperatorExpr(less, $1, $3); }
                | ExprWithBlock '<' ExprWithBlock			{ $$ = OperatorExpr(less, $1, $3); }
                | ExprWithoutBlock GREATER_EQUAL ExprWithoutBlock	{ $$ = OperatorExpr(greater_equal, $1, $3); }
                | ExprWithoutBlock GREATER_EQUAL ExprWithBlock		{ $$ = OperatorExpr(greater_equal, $1, $3); }
                | ExprWithBlock GREATER_EQUAL ExprWithoutBlock		{ $$ = OperatorExpr(greater_equal, $1, $3); }
                | ExprWithBlock GREATER_EQUAL ExprWithBlock		{ $$ = OperatorExpr(greater_equal, $1, $3); }
                | ExprWithoutBlock LESS_EQUAL ExprWithoutBlock		{ $$ = OperatorExpr(less_equal, $1, $3); }
                | ExprWithoutBlock LESS_EQUAL ExprWithBlock		{ $$ = OperatorExpr(less_equal, $1, $3); }
                | ExprWithBlock LESS_EQUAL ExprWithoutBlock		{ $$ = OperatorExpr(less_equal, $1, $3); }
                | ExprWithBlock LESS_EQUAL ExprWithBlock		{ $$ = OperatorExpr(less_equal, $1, $3); }
                | ExprWithBlock '?'					{ $$ = OperatorExpr(qt, $1, 0); }
                | ExprWithoutBlock '?'					{ $$ = OperatorExpr(qt, $1, 0); }
                | '-' ExprWithBlock %prec UMINUS			{ $$ = OperatorExpr(uminus, $2, 0); }
                | '-' ExprWithoutBlock %prec UMINUS			{ $$ = OperatorExpr(uminus, $2, 0); }
                | '!' ExprWithBlock					{ $$ = OperatorExpr(neg, $2, 0); }
                | '!' ExprWithoutBlock					{ $$ = OperatorExpr(neg, $2, 0); }
                | ExprWithBlock OR ExprWithBlock			{ $$ = OperatorExpr(or, $1, $3); }
                | ExprWithoutBlock OR ExprWithBlock			{ $$ = OperatorExpr(or, $1, $3); }
                | ExprWithBlock OR ExprWithoutBlock			{ $$ = OperatorExpr(or, $1, $3); }
                | ExprWithoutBlock OR ExprWithoutBlock			{ $$ = OperatorExpr(or, $1, $3); }
                | ExprWithBlock AND ExprWithBlock			{ $$ = OperatorExpr(and, $1, $3); }
                | ExprWithoutBlock AND ExprWithBlock			{ $$ = OperatorExpr(and, $1, $3); }
                | ExprWithBlock AND ExprWithoutBlock			{ $$ = OperatorExpr(and, $1, $3); }
                | ExprWithoutBlock AND ExprWithoutBlock			{ $$ = OperatorExpr(and, $1, $3); }
                | ExprWithBlock '=' ExprWithBlock			{ $$ = OperatorExpr(asgn, $1, $3); }
                | ExprWithoutBlock '=' ExprWithBlock			{ $$ = OperatorExpr(asgn, $1, $3); }
                | ExprWithBlock '=' ExprWithoutBlock			{ $$ = OperatorExpr(asgn, $1, $3); }
                | ExprWithoutBlock '=' ExprWithoutBlock			{ $$ = OperatorExpr(asgn, $1, $3); }
                | BREAK ExprWithBlock					{ $$ = OperatorExpr(break_expr, $2, 0); }
                | BREAK ExprWithoutBlock				{ $$ = OperatorExpr(break_expr, $2, 0); }
                | BREAK							{ $$ = OperatorExpr(break_expr, 0, 0); }
                | CONTINUE						{ $$ = OperatorExpr(continue_expr, 0, 0); }
                | '(' ExprWithBlock ')'					{ $$ = $2; }
                | '(' ExprWithoutBlock ')'				{ $$ = $2; }
                | '[' ExprList_final ']'				{ $$ = ArrExprFromList($2); }
                | '[' ExprWithBlock ';' ExprWithBlock ']'		{ $$ = ArrExprAutoFill($2, $4); }
                | '[' ExprWithoutBlock ';' ExprWithBlock ']'		{ $$ = ArrExprAutoFill($2, $4); }
                | '[' ExprWithBlock ';' ExprWithoutBlock ']'		{ $$ = ArrExprAutoFill($2, $4); }
                | '[' ExprWithoutBlock ';' ExprWithoutBlock ']'		{ $$ = ArrExprAutoFill($2, $4); }
                | ExprWithBlock '[' ExprWithBlock ']'                   { $$ = OperatorExpr(index_expr, $1, $3); }
                | ExprWithoutBlock '[' ExprWithBlock ']'		{ $$ = OperatorExpr(index_expr, $1, $3); }
                | ExprWithBlock '[' ExprWithoutBlock ']'		{ $$ = OperatorExpr(index_expr, $1, $3); }
                | ExprWithoutBlock '[' ExprWithoutBlock ']'		{ $$ = OperatorExpr(index_expr, $1, $3); }
                | ID '(' ExprList_final ')'            			{ $$ = CallAccessExpr(call_expr, $1, 0, $3); }
                | ExprWithBlock '.' ID '(' ExprList_final ')'   	{ $$ = CallAccessExpr(method_expr, $3, $1, $5); }
                | ExprWithoutBlock '.' ID '(' ExprList_final ')'	{ $$ = CallAccessExpr(method_expr, $3, $1, $5); }
                | ExprWithBlock '.' ID                          	{ $$ = CallAccessExpr(field_access_expr, $3, $1, 0); }
                | ExprWithoutBlock '.' ID				{ $$ = CallAccessExpr(field_access_expr, $3, $1, 0); }
                | ExprWithBlock RANGE ExprWithBlock			{ $$ = RangeExpr(range_expr, $1, $3); }
                | ExprWithoutBlock RANGE ExprWithBlock			{ $$ = RangeExpr(range_expr, $1, $3); }
                | ExprWithBlock RANGE ExprWithoutBlock			{ $$ = RangeExpr(range_expr, $1, $3); }
                | ExprWithoutBlock RANGE ExprWithoutBlock		{ $$ = RangeExpr(range_expr, $1, $3); }
                | ExprWithBlock RANGE					{ $$ = RangeExpr(range_left, $1, 0); }
                | ExprWithoutBlock RANGE				{ $$ = RangeExpr(range_left, $1, 0); }
                | RANGE ExprWithBlock					{ $$ = RangeExpr(range_right, $2, 0); }
                | RANGE ExprWithoutBlock				{ $$ = RangeExpr(range_right, $2, 0); }
                | RANGE							{ $$ = RangeExpr(range_right, 0, 0); }
                | ExprWithBlock RANGE_IN ExprWithBlock			{ $$ = RangeExpr(range_in_expr, $1, $3); }
                | ExprWithoutBlock RANGE_IN ExprWithBlock		{ $$ = RangeExpr(range_in_expr, $1, $3); }
                | ExprWithBlock RANGE_IN ExprWithoutBlock		{ $$ = RangeExpr(range_in_expr, $1, $3); }
                | ExprWithoutBlock RANGE_IN ExprWithoutBlock		{ $$ = RangeExpr(range_in_expr, $1, $3); }
                | RANGE_IN ExprWithBlock				{ $$ = RangeExpr(range_in_right, $2, 0); }
                | RANGE_IN ExprWithoutBlock				{ $$ = RangeExpr(range_in_right, $2, 0); }
                | RETURN ExprWithBlock					{ $$ = OperatorExpr(return_expr, $2, 0); }
                | RETURN ExprWithoutBlock				{ $$ = OperatorExpr(return_expr, $2, 0); }
                | RETURN						{ $$ = OperatorExpr(return_expr, 0, 0); }
                | ID							{ $$ = CallAccessExpr(id, $1, 0, 0); }
                ;

//------------------ExprWithBlock-------------------
ExprWithBlock: LOOP BlockExpr						{ $$ = CycleExpr(loop_expr, 0, $2, 0); }
             | WHILE ExprWithBlock BlockExpr				{ $$ = CycleExpr(loop_while, $2, $3, 0); }
             | WHILE ExprWithoutBlock BlockExpr				{ $$ = CycleExpr(loop_while, $2, $3, 0); }
             | FOR ID IN ExprWithBlock BlockExpr			{ $$ = CycleExpr(loop_for, $4, $5, $2); }
             | FOR ID IN ExprWithoutBlock BlockExpr			{ $$ = CycleExpr(loop_for, $4, $5, $2); }
             | IF ExprWithBlock BlockExpr				{ $$ = IfExpr($2, $3); }
             | IF ExprWithoutBlock BlockExpr				{ $$ = IfExpr($2, $3); }
             | IF ExprWithBlock BlockExpr ELSE BlockExpr		{ $$ = IfExpr($2, $3, $5); }
             | IF ExprWithoutBlock BlockExpr ELSE BlockExpr		{ $$ = IfExpr($2, $3, $5); }
             ;

BlockExpr: '{' StmtList '}'						{ $$ = BlockExpr($2); }
         | '{' '}'							{ $$ = BlockExpr(0); }
         ;

//--------------------Statement---------------------

StmtList: Stmt								{ $$ = StmtListNode($1); }
        | StmtList Stmt							{ $$ = StmtListAdd($1, $2); }
        ;

Stmt: ';'								{ $$ = StmtNode(semicolon, 0, 0, 0); }
    | ExprWithoutBlock ';'						{ $$ = StmtNode(expr, $1, 0, 0); }
    | ExprWithBlock ';'              					{ $$ = StmtNode(expr, $1, 0, 0); }
    | LetStmt								{ $$ = StmtNode(let, 0, 0, $1); }
    | DeclarationStmt							{ $$ = StmtNode(declaration, 0, $1, 0); }
    ;


LetStmt: LET ID ':' Type '=' ExprWithBlock ';'				{ $$ = LetStmt($2, $4, notMut, $6); }
       | LET ID ':' Type '=' ExprWithoutBlock ';'			{ $$ = LetStmt($2, $4, notMut, $6); }
       | LET ID '=' ExprWithBlock ';'					{ $$ = LetStmt($2, 0, notMut, $4); }
       | LET ID '=' ExprWithoutBlock ';'				{ $$ = LetStmt($2, 0, notMut, $4); }
       | LET MUT ID ':' Type '=' ExprWithBlock ';'			{ $$ = LetStmt($3, $5, mut, $7); }
       | LET MUT ID ':' Type '=' ExprWithoutBlock ';'			{ $$ = LetStmt($3, $5, mut, $7); }
       | LET MUT ID '=' ExprWithBlock ';'				{ $$ = LetStmt($3, 0, mut, $5); }
       | LET MUT ID '=' ExprWithoutBlock ';'				{ $$ = LetStmt($3, 0, mut, $5); }
       | LET MUT ID ':' Type ';'					{ $$ = LetStmt($3, $5, mut, 0); }
       | LET MUT ID ';'							{ $$ = LetStmt($3, 0, mut, 0); }
       | LET ID ':' Type ';'						{ $$ = LetStmt($2, $4, notMut, 0); }
       | LET ID ';'							{ $$ = LetStmt($2, 0, notMut, 0); }
       ;

//---------DeclarationStatement---------
DeclarationStmt: Enum							{ $$ = DeclarationEnum(self, $1); }
               | Visibility Enum					{ $$ = DeclarationEnum($1, $2); }
               | Function						{ $$ = DeclarationFunction(self, $1); }
               | Visibility Function					{ $$ = DeclarationFunction($1, $2); }
               | ConstStmt						{ $$ = DeclarationConst(self, $1); }
               | Visibility ConstStmt					{ $$ = DeclarationConst($1, $2); }
               | Struct							{ $$ = DeclarationStruct(self, $1); }
               | Visibility Struct					{ $$ = DeclarationStruct($1, $2); }
               | Trait							{ $$ = DeclarationTrait(self, $1); }
               | Visibility Trait					{ $$ = DeclarationTrait($1, $2); }
               | Impl							{ $$ = DeclarationImpl(self, $1); }
               | Visibility Impl					{ $$ = DeclarationImpl($1, $2); }
               ;

//----Enum----
Enum: ENUM ID '{' EnumItems_final '}'					{ $$ = EnumNode($2, $4); }
    ;

EnumItems_final: /*empty*/						{ $$ = EnumListFinal(0); }
               | EnumItems						{ $$ = EnumListFinal($1); }
               | EnumItems ','						{ $$ = EnumListFinal($1); }
               ;

EnumItems: EnumItem							{ $$ = EnumListNode($1); }
         | EnumItems ',' EnumItem					{ $$ = EnumListAdd($1, $3); }
         ;

EnumItem: Visibility ID							{ $$ = EnumItemNode($2, $1, 0, 0); }
        | ID								{ $$ = EnumItemNode($1, 0, 0, 0); }
        | Visibility ID '=' ExprWithBlock				{ $$ = EnumItemNode($2, $1, 0, $4); }
        | Visibility ID '=' ExprWithoutBlock				{ $$ = EnumItemNode($2, $1, 0, $4); }
        | ID '=' ExprWithBlock						{ $$ = EnumItemNode($1, 0, 0, $3); }
        | ID '=' ExprWithoutBlock					{ $$ = EnumItemNode($1, 0, 0, $3); }
        | Visibility ID '{' StructFields_final '}'			{ $$ = EnumItemNode($2, $1, $4, 0); }
        | ID '{' StructFields_final '}'					{ $$ = EnumItemNode($1, 0, $3, 0); }
        ;

//----Function----
Function: FN ID '(' FuncParamList_final ')' RIGHT_ARROW Type BlockExpr	{ $$ = FunctionNode($2, $7, $4, $8); }
        | FN ID '(' FuncParamList_final ')' RIGHT_ARROW Type ';'	{ $$ = FunctionNode($2, $7, $4, 0); }
        | FN ID '(' FuncParamList_final ')' BlockExpr			{ $$ = FunctionNode($2, 0, $4, $6); }
        | FN ID '(' FuncParamList_final ')' ';'				{ $$ = FunctionNode($2, 0, $4, 0); }
        ;

FuncParamList_final: /*empty*/						{ $$ = FunctionParamsFinal(0); }
                   | FuncParamList					{ $$ = FunctionParamsFinal($1); }
                   | FuncParamList ','					{ $$ = FunctionParamsFinal($1); }
                   ;

FuncParamList: FuncParam						{ $$ = FunctionParamsNode($1); }
             | FuncParamList ',' FuncParam				{ $$ = FunctionParamsAdd($1, $3); }
             ;

FuncParam: ID ':' Type							{ $$ = FunctionParamNode($1, $3, notMut); }
         | MUT ID ':' Type						{ $$ = FunctionParamNode($2, $4, mut); }
         ;

//-----Struct-----

Struct: STRUCT ID '{' StructFields_final '}'				{ $$ = StructNode($2, $4); }
      | STRUCT ID ';'							{ $$ = StructNode($2, 0); }
      ;

StructFields_final: /*empty*/						{ $$ = StructListFinal(0); }
                  | StructFields					{ $$ = StructListFinal($1); }
                  | StructFields ','					{ $$ = StructListFinal($1); }
                  ;

StructFields: StructField						{ $$ = StructListNode($1); }
            | StructFields ',' StructField				{ $$ = StructListAdd($1, $3); }
            ;

StructField: Visibility ID ':' Type					{ $$ = StructItemNode($2, $4, $1); }
           | ID ':' Type						{ $$ = StructItemNode($1, $3, self); }
           ;

//---------Implementation---------
Impl: IMPL Type '{' AssociatedItems_final '}'				{ $$ = ImplNode(inherent, $2, 0, $4); }
    | IMPL ID FOR Type '{' AssociatedItems_final '}'			{ $$ = ImplNode(trait, $4, $2, $6); }
    ;

//-------------Trait-------------
Trait: TRAIT ID '{' AssociatedItems_final '}'				{ $$ = TraitNode($2, $4); }
;

AssociatedItems_final: /*empty*/					{ $$ = AssociatedListFinal(0); }
                     | AssociatedItems					{ $$ = AssociatedListFinal($1); }
                     ;

AssociatedItems: AssociatedItem						{ $$ = AssociatedList($1); }
               | AssociatedItems AssociatedItem				{ $$ = AssociatedListAdd($1, $2); }
               ;

AssociatedItem: Visibility Function					{ $$ = AssociatedItemNode($1, $2, 0); }
              | Function						{ $$ = AssociatedItemNode(0, $1, 0); }
              | Visibility ConstStmt					{ $$ = AssociatedItemNode($1, 0, $2); }
              | ConstStmt						{ $$ = AssociatedItemNode(0, 0, $1); }
              ;

//---------ConstStatement---------
ConstStmt: CONST ID ':' Type ';'					{ $$ = ConstStmt($2, $4, 0); }
         | CONST ID ':' Type '=' ExprWithBlock ';'			{ $$ = ConstStmt($2, $4, $6); }
         | CONST ID ':' Type '=' ExprWithoutBlock ';'			{ $$ = ConstStmt($2, $4, $6); }
         ;

//---------Type---------
Type: INT								{ $$ = int_; }
    | STRING								{ $$ = string_; }
    | CHAR								{ $$ = char_; }
    | FLOAT								{ $$ = float_; }
    | BOOL								{ $$ = bool_; }
    | ID								{ $$ = id_; }
    ;

//---------Visibility---------
Visibility: PUB								{ $$ = pub; }
          | PUB '(' CRATE ')'						{ $$ = crate; }
          | PUB '(' SELF ')'						{ $$ = self; }
          | PUB '(' SUPER ')'						{ $$ = super; }
          ;
%%