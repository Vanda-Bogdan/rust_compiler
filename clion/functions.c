#include "nodes.h"

/**
 * Global id of nodes (incremental)
 */
int global_id = 0;

/*------------------------------------------------ExprFunctions-------------------------------------------------------*/
struct expr_node* OperatorExpr(enum expr_type type, struct expr_node* left, struct expr_node* right) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

//------------------------------------ExprFromLiterals
struct expr_node* ExprFromBoolLiteral(bool value) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = bool_lit;
    new_node->Bool = value;
    return new_node;
}

struct expr_node* ExprFromIntLiteral(int value) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = int_lit;
    new_node->Int = value;
    return new_node;
}

struct expr_node* ExprFromFloatLiteral(float value) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = float_lit;
    new_node->Float = value;
    return new_node;
}

struct expr_node* ExprFromCharLiteral(char value) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = char_lit;
    new_node->Char = value;
    return new_node;
}

struct expr_node* ExprFromStringLiteral(char* value) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = string_lit;
    new_node->String = value;
    return new_node;
}

//--------------------------------------CallAccessExpr
struct expr_node* CallAccessExpr(enum expr_type type, char* name, struct expr_node* expr, struct expr_list_node* expr_list) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = type;
    new_node->Name = name;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

//-------------------------------------ExprList
struct expr_list_node* ExprList(struct expr_node* expr) {
    struct expr_list_node* new_node = (struct expr_list_node*) malloc(sizeof (struct expr_list_node));
    new_node->ID = global_id++;
    new_node->first = expr;
    new_node->last = expr;
    return new_node;
}

struct expr_list_node* ExprListAdd(struct expr_list_node* expr_list, struct expr_node* expr) {
    expr_list->last->next = expr;
    expr_list->last = expr;
}

struct expr_list_node* ExprListFinal(struct expr_list_node* expr_list) {
    return expr_list;
}

//-------------------------------------ArrExpr
struct expr_node* ArrExprFromList(struct expr_list_node* expr_list) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = array_expr;
    new_node->expr_list = expr_list;
    return new_node;
}

struct expr_node* ArrExprAutoFill(struct expr_node* first, struct expr_node* second) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = array_expr_auto_fill;
    new_node->expr_left = first;
    new_node->expr_right = second;
    return new_node;
}

//------------------------------------RangeExpr
struct expr_node* RangeExpr(enum expr_type type, struct expr_node* left, struct  expr_node* right) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

