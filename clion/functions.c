#include "nodes.h"

struct expr_node* Expr(int ID, enum expr_type type, struct expr_node* left, struct expr_node* right){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = ID;
    new_node->expr_left = left;
    new_node->expr_right = right;
    new_node->type = type;

    return new_node;
}

struct expr_node* ExprFromType(enum expr_type type){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->type = type;

    return new_node;
}

struct expr_node* ExprList(struct expr_node* item){

    item->next = NULL;

    return item;
}

struct expr_node* ExprListAdd(struct expr_node* list, struct expr_node* item){

    struct expr_node* cur_node = list;
    while(cur_node->next!=NULL){
        cur_node = cur_node->next;
    }
    cur_node->next = item;
    item->next = NULL;

    return list;
}

struct expr_node* ExprFromArray(struct expr_node* left, struct expr_node* right){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->expr_left = left;
    new_node->expr_right = right;
    new_node->type = array_expr;

    return new_node;
}

struct expr_node* ExprFromIndex(struct expr_node* left, struct expr_node* right){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->expr_left = left;
    new_node->expr_right = right;
    new_node->type = index_expr;

    return new_node;
}

struct expr_node* ExprFromRange(struct expr_node* left, struct expr_node* right){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->expr_left = left;
    new_node->expr_right = right;
    new_node->type = range_expr;

    return new_node;
}

struct expr_node* ExprFromRangeIn(struct expr_node* left, struct expr_node* right){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->expr_left = left;
    new_node->expr_right = right;
    new_node->type = rangein_expr;

    return new_node;
}

struct expr_node* ExprFromReturn(struct expr_node* expr){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->expr_left = expr;
    new_node->type = return_expr;

    return new_node;
}

struct expr_node* ExprFromId(char * Id){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->String = Id;
    new_node->type = id;

    return new_node;
}

struct expr_node* ExprFromCall(char * Id, struct expr_node* parameters_list){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->String = Id;
    new_node->type = call_expr;
    new_node->expr_left = parameters_list;

    return new_node;
}

struct expr_node* ExprFromMethod(char * Id, struct expr_node* this_expr, struct expr_node* parameters_list){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->String = Id;
    new_node->type = method_expr;
    new_node->expr_left = this_expr;
    new_node->expr_right = parameters_list;

    return new_node;
}

struct expr_node* ExprFromField(char * Id, struct expr_node* this_expr){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->String = Id;
    new_node->type = field_access_expr;
    new_node->expr_left = this_expr;

    return new_node;
}

struct expr_node* ExprFromCharLiteral(char char_lit){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->Char = char_lit;

    return new_node;
}

struct expr_node* ExprFromStringLiteral(char* str_lit){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->String = str_lit;

    return new_node;
}

struct expr_node* ExprFromIntLiteral(int int_lit){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->Int = int_lit;

    return new_node;
}

struct expr_node* ExprFromFloatLiteral(float float_lit){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->Float = float_lit;

    return new_node;
}

struct expr_node* ExprFromTrue(bool bool_lit_true){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->Bool = bool_lit_true;

    return new_node;
}

struct expr_node* ExprFromFalse(bool bool_lit_false){

    struct expr_node* new_node = (struct expr_node*) malloc(sizeof (struct expr_node));
    new_node->Bool = bool_lit_false;

    return new_node;
}