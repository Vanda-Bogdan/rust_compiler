#include "stdlib.h"
#include <stdbool.h>

/*--------------------------------------------------Type--------------------------------------------------------------*/
enum type {
    int_, char_, string_, float_, bool_, id_
};

/*----------------------------------------------------Visibility------------------------------------------------------*/
enum visibility {
    pub, crate, self, super
};

/*---------------------------------------------------Mutable----------------------------------------------------------*/
enum mutable {
    notMut, mut
};

/*-----------------------------------------------------Expression-----------------------------------------------------*/
enum expr_type{
    plus, minus, mul, div_expr, rem, equal, not_equal, greater, less, greater_equal,
    less_equal, qt, uminus, neg, or, and, asgn, break_expr, continue_expr, return_expr, empty, array_expr, index_expr, range_expr, rangein_expr,
    id, call_expr, method_expr, field_access_expr, if_expr, loop_expr, loop_while
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
    struct stmt_node * body;
    struct stmt_node * else_body;
    struct stmt_list_node* stmt_list;
};

struct expr_list_node {
    int ID;
    struct expr_node* first;
    struct expr_node* last;
};

/*---------------------------------------------------Statement--------------------------------------------------------*/
enum stmt_type {
    semicolon, expr_stmt, stmtWithBlock, declaration, let
};

struct stmt_node{
    int ID;
    enum stmt_type type;
    struct expr_node* expr;
    enum visibility visibility;
    struct decl_stmt_node* decl_stmt;
    struct let_stmt_node* let_stmt;
    struct stmt_node* next;
};

struct stmt_list_node {
    int ID;
    struct stmt_node* first;
    struct stmt_node* last;
};

/*---------------------------------------------------LetStmt----------------------------------------------------------*/
struct let_stmt_node {
    int ID;
    char* name;
    enum mutable mutable;
    enum type type;
    struct expr_node* expr;
};

/*--------------------------------------DeclarationStmt---------------------------------------------------------------*/
enum decl_stmt_type {
    enum_, function_, constStmt_, struct_, trail_, impl_
};

struct decl_stmt_node {
    int ID;
    enum decl_stmt_type type;
    struct struct_node* struct_item;
    struct function_node* function_item;
    struct enum_node* enum_item;
    struct const_stmt_node* const_stmt_item;
    struct trait_node* trait_item;
    struct impl_node* impl_item;
};

/*---------------------------------------------------Struct-----------------------------------------------------------*/
struct struct_item_node {
    int ID;
    char* name;
    struct struct_item_node* next;
    enum type type;
    enum visibility visibility;
};

struct struct_node {
    int ID;
    char* name;
    struct struct_list_node* items;
};

struct struct_list_node {
    int ID;
    struct struct_item_node* first;
    struct struct_item_node* last;
};

/*----------------------------------------------------Enum------------------------------------------------------------*/
struct enum_node {
    int ID;
    char* name;
    struct enum_list_node* items;
};

struct enum_item_node {
    int ID;
    enum visibility visibility;
    char* name;
    struct enum_item_node* next;
    struct struct_list_node* struct_list;
};

struct enum_list_node {
    int ID;
    struct enum_item_node* first;
    struct enum_item_node* last;
};

/*--------------------------------------------------Function----------------------------------------------------------*/
struct function_param_node {
    int ID;
    char* name;
    enum mutable mutable;
    struct function_param_node* next;
    enum type type;
};

struct function_node {
    int ID;
    char* name;
    struct function_params_node* params;
    struct expr_node* body;
};

struct function_params_node {
    int ID;
    struct function_param_node* first;
    struct function_param_node* last;
};

/*-------------------------------------------------ConstStmt----------------------------------------------------------*/
struct const_stmt_node {
    int ID;
    char* name;
    enum type type;
    struct expr_node* expr;
};

/*-------------------------------------------------Trait--------------------------------------------------------------*/
struct associated_item_node {
    int ID;
    char* name;
    struct associated_item_node* next;
    struct function_node* fn;
    enum visibility visibility;
    struct const_stmt_node* const_stmt;
};

struct trait_node {
    int ID;
    char* name;
    struct associated_items_node* items;
};

struct associated_items_node {
    int ID;
    struct associated_item_node* first;
    struct associated_item_node* last;
};

/*------------------------------------------------Impl----------------------------------------------------------------*/
enum impl_type {
    inherent, trait
};

struct impl_node {
    int ID;
    char* name;
    enum impl_type implType;
    enum type type;
    struct associated_items_node* items;
};

/*---------------------------------------------------FinalNode--------------------------------------------------------*/
struct program_node {
    int ID;
    struct function_node* main;
};


