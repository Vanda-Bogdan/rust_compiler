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

//--------------------------------------IfExpr
struct expr_node* IfExpr(struct expr_node* condition, struct expr_node* body, struct expr_node* else_body) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = if_expr;
    new_node->expr_left = condition;
    new_node->body = body;
    new_node->else_body = else_body;
    return new_node;
}

//--------------------------------------CycleExpr
struct expr_node* CycleExpr(enum expr_type type, struct expr_node* condition, struct expr_node* body, char* id) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = type;
    new_node->expr_left = condition;
    new_node->body = body;
    new_node->Name = id;
    return new_node;
}

//-------------------------------------BlockExpr
struct expr_node* BlockExpr(struct stmt_list_node* stmt_list) {
    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = global_id++;
    new_node->type = block_expr;
    new_node->stmt_list = stmt_list;
    return new_node;
}

/*-------------------------------------------------StmtFunctions------------------------------------------------------*/

//-------------------------------------ConstStmt
struct const_stmt_node* ConstStmt(char* name, enum type type, struct expr_node* expr) {
    struct const_stmt_node* new_node = (struct const_stmt_node*) malloc(sizeof (struct const_stmt_node));
    new_node->ID = global_id++;
    new_node->type = type;
    new_node->name = name;
    new_node->expr = expr;
    return new_node;
}

//-----------------------------------Trait
struct trait_node* TraitNode(char* name, struct associated_items_node* items) {
    struct trait_node* new_node = (struct trait_node*) malloc(sizeof (struct trait_node));
    new_node->ID = global_id++;
    new_node->name = name;
    new_node->items = items;
    return new_node;
}

//----------------------------------AssociatedItem
struct associated_item_node* AssociatedItemNode(enum visibility vis, struct function_node* fn, struct const_stmt_node* const_stmt) {
    struct associated_item_node* new_node = (struct associated_item_node*) malloc(sizeof (struct associated_item_node));
    new_node->ID = global_id++;
    new_node->visibility = vis;
    new_node->fn = fn;
    new_node->const_stmt = const_stmt;
    return new_node;
}

//---------------------------------AssociatedList
struct associated_items_node* AssociatedList(struct associated_item_node* node) {
    struct associated_items_node* new_node = (struct associated_items_node*) malloc(sizeof (struct associated_items_node));
    new_node->ID = global_id++;
    new_node->first = node;
    new_node->last = node;
    return new_node;
}

struct associated_items_node* AssociatedListAdd(struct associated_items_node* list, struct associated_item_node* last) {
    list->last->next = last;
    list->last = last;
}

struct associated_items_node* AssociatedListFinal(struct associated_items_node* list) {
    return list;
}

//-------------------------------------Impl
struct impl_node* ImplNode(enum impl_type impl_type, enum type type, char* name, struct associated_items_node* list) {
    struct impl_node* new_node = (struct impl_node*) malloc(sizeof (struct impl_node));
    new_node->ID = global_id++;
    new_node->implType = impl_type;
    new_node->type = type;
    new_node->name = name;
    new_node->items = list;
    return new_node;
}

