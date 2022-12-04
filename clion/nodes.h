#pragma once
#include "stdlib.h"
#include <stdbool.h>

/*--------------------------------------------------Type--------------------------------------------------------------*/
enum type {
    emptyType, int_, char_, string_, float_, bool_, id_, array_
};

struct type_node{
    int ID;
    char * name;
    enum type type;
    struct type_node* typeArr;
    struct expr_node* exprArr;
};

/*----------------------------------------------------Visibility------------------------------------------------------*/
enum visibility {
    emptyVisibility, pub, crate, self, super
};

/*---------------------------------------------------Mutable----------------------------------------------------------*/
enum mutable {
    notMut, mut
};

/*-----------------------------------------------------Expression-----------------------------------------------------*/
enum expr_type{
    plus, minus, mul, div_expr, equal, not_equal, greater, less, greater_equal,
    less_equal, qt, uminus, neg, or, and, asgn, break_expr, continue_expr,
    return_expr, array_expr, array_expr_auto_fill, index_expr,
    range_expr, range_in_expr, range_left, range_right, range_in_right,
    id, self_expr, call_expr, method_expr, field_access_expr, if_expr, loop_expr, loop_while, loop_for, block_expr,
    int_lit, float_lit, char_lit, string_lit, bool_lit, struct_expr, struct_field_expr, static_method
};

struct expr_node {
    int ID;
    int Int;
    float Float;
    bool Bool;
    char* String;
    char* ParentID;
    char Char;
    char * Name;
    enum expr_type type;
    struct expr_node * expr_left;
    struct expr_node * expr_right;
    struct expr_node * next;
    struct expr_list_node * expr_list;
    struct expr_node * body;
    struct expr_node * else_body;
    struct stmt_list_node* stmt_list;
};

struct expr_list_node {
    int ID;
    struct expr_node* first;
    struct expr_node* last;
};

/*---------------------------------------------------Statement--------------------------------------------------------*/
enum stmt_type {
    semicolon, expr, declaration, let
};

struct stmt_node{
    int ID;
    enum stmt_type type;
    struct expr_node* expr;
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
    struct type_node* type;
    struct expr_node* expr;
};

/*--------------------------------------DeclarationStmt---------------------------------------------------------------*/
enum decl_stmt_type {
    enum_, function_, constStmt_, struct_, trait_, impl_
};

struct decl_stmt_node {
    int ID;
    enum visibility visibility;
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
    struct type_node* type;
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
    struct expr_node* expr;
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
    struct type_node* type;
};

enum func_type {
    method_self, method_mut_self, associated
};

struct function_node {
    int ID;
    char* name;
    struct type_node* returnType;
    struct function_params_node* params;
    struct expr_node* body;
};

struct function_params_node {
    int ID;
    enum func_type funcType;
    struct function_param_node* first;
    struct function_param_node* last;
};

/*-------------------------------------------------ConstStmt----------------------------------------------------------*/
struct const_stmt_node {
    int ID;
    char* name;
    struct type_node* type;
    struct expr_node* expr;
};

/*-------------------------------------------------Trait--------------------------------------------------------------*/
struct associated_item_node {
    int ID;
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
    struct type_node* type;
    struct associated_items_node* items;
};

/*---------------------------------------------------FinalNode--------------------------------------------------------*/
struct program_node {
    int ID;
    //struct function_node* main;
    struct stmt_list_node* stmt_list;
};


