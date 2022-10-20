#include "stdlib.h"
#include <stdbool.h>

enum expr_type{
    plus, minus,
};

struct expr_node {

    int ID;
    int Int;
    float Float;
    bool Bool;
    char * Name;
    enum expr_type type;
    struct expr_node * expr_left;
    struct expr_node * expr_right;

};

struct expr_node* createExpr(int ID, enum expr_type, ){

}

struct expr_node* createBinaryExpr(int ID, enum expr_type type, struct expr_node* left, struct expr_node* right){

    struct expr_node* new_node = malloc(sizeof (struct expr_node));
    new_node->expr_left = left;
    new_node->expr_right = right;
    new_node->type = type;

    return new_node;
}

struct expr_node* ExprFromCharLiteral(char * str){
    struct expr_node* new_node = malloc(sizeof (struct expr_node));
}






