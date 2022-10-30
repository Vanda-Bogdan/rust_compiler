#include "stdlib.h"
#include <stdbool.h>

//------------------------Expression-----------------------------------
enum expr_type{
    plus, minus, mul, div_expr, rem, equal, not_equal, greater, less, greater_equal,
    less_equal, qt, uminus, neg, or, and, asgn, plus_asgn, minus_asgn, mul_asgn, div_asgn, rem_asgn,
    break_expr, continue_expr, return_expr, empty, array_expr, index_expr, range_expr, rangein_expr,
    id, call_expr, method_expr, field_access_expr,
};

struct expr_node {

    int ID;
    int Int;
    float Float;
    bool Bool;
    char* String;
    char Char;
    char * Name;
    enum expr_type type;
    struct expr_node * expr_left;
    struct expr_node * expr_right;
    struct expr_node * next;
};


//------------------------Statement-----------------------------------
enum stmt_type {
    Semicolon, Expr_stmt, StmtWithBlock, Let, Other
};

struct stmt_node{
    enum stmt_type type;
    struct expr_node* expr;

};