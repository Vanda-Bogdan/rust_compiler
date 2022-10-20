#include "stdlib.h"
#include <stdbool.h>

enum expr_type{
    plus, minus, mul, div, rem, equal, not_equal, greater, less, greater_equal,
    less_equal, qt, uminus, neg, or, and, asgn, plus_asgn, minus_asgn, mul_asgn, div_asgn, rem_asgn
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

};

struct expr_node* createExpr(int ID, enum expr_type type, struct expr_node* left, struct expr_node* right){

    struct expr_node* new_node = (expr_node*) malloc(sizeof (struct expr_node));
    new_node->ID = ID;
    new_node->expr_left = left;
    new_node->expr_right = right;
    new_node->type = type;

    return new_node;
}

struct expr_node* ExprFromCharLiteral(char char_lit){

    struct expr_node* new_node = (expr_node*) malloc(sizeof (struct expr_node));
    new_node->Char = char_lit;

    return new_node;
}

struct expr_node* ExprFromStringLiteral(char* str_lit){

    struct expr_node* new_node = (expr_node*) malloc(sizeof (struct expr_node));
    new_node->String = str_lit;

    return new_node;
}

struct expr_node* ExprFromIntLiteral(int int_lit){

    struct expr_node* new_node = (expr_node*) malloc(sizeof (struct expr_node));
    new_node->Int = int_lit;

    return new_node;
}

struct expr_node* ExprFromFloatLiteral(float float_lit){

    struct expr_node* new_node = (expr_node*) malloc(sizeof (struct expr_node));
    new_node->Float = float_lit;

    return new_node;
}

struct expr_node* ExprFromTrue(bool bool_lit_true){

    struct expr_node* new_node = (expr_node*) malloc(sizeof (struct expr_node));
    new_node->Bool = bool_lit_true;

    return new_node;
}

struct expr_node* ExprFromFalse(bool bool_lit_false){

    struct expr_node* new_node = (expr_node*) malloc(sizeof (struct expr_node));
    new_node->Bool = bool_lit_false;

    return new_node;
}






