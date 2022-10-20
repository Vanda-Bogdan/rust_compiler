#include "stdlib.h"
#include <stdbool.h>

enum expr_type{
    plus,
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

struct expr_node* createBinaryExpr(int ID, enum expr_type, struct expr_node){

}

