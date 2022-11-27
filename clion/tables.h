#pragma once
#include "stdlib.h"
#include <stdbool.h>
#include <string.h>
#include "nodes.h"

enum constant {
    Utf8 = 1,
    Class = 7,
    Methodref = 10,
    NameAndType = 12,
    Integer = 3,
    Float = 4
};

struct table_item* table;
const int null = -1;
int countID = 0;
int getID() {
    return countID++;
}

struct table_item{
    int ID;
    enum constant type;
    struct item_value * value;
    struct table_item * next;
};

struct item_value{
    char* string;
    int first;
    int second;
};

struct table_item* createTable(){
    struct table_item* new_item = (struct table_item*) malloc(sizeof (struct table_item));
    new_item->next = NULL;
    new_item->value = NULL;

    return new_item;
}

struct table_item* appendTo(struct table_item* item){
    struct table_item* new_item = (struct table_item*) malloc(sizeof (struct table_item));
    new_item->next = NULL;
    new_item->value = NULL;
    item->next = new_item;

    return new_item;
}

struct table_item* searchByID(struct table_item* first, int ID){

    struct table_item* current = first;
    while(current != NULL){
        if(current->ID == ID){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct table_item* searchByString(struct table_item* first, char* string){

    struct table_item* current = first;
    while(current != NULL){
        if(current->value!=NULL && strcmp(current->value->string, string) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct item_value* createValue(char * string, int first, int second){
    struct item_value* new_item = (struct item_value*) malloc(sizeof (struct item_value));
    new_item->string = string;
    new_item->first = first;
    new_item->second = first;

    return new_item;
}

struct table_item* createRecord(enum constant type, char* str, int first, int second) {
    struct table_item* tableItem = appendTo(table);
    tableItem->ID = getID();
    tableItem->type = type;
    tableItem->value = createValue(str, first, second);
    return tableItem;
}

//-----Tree-------
void stmt_list_table(struct stmt_list_node *stmt_list);
void stmt_table(struct stmt_node* stmt_node);
void enum_stmt_table(struct enum_node* enum_node);

int tree_make_table(struct program_node *prg){

    stmt_list_table(prg->stmt_list);

    return 0;
}

void stmt_list_table(struct stmt_list_node *stmt_list){
    struct stmt_node *current = stmt_list->first;
    while(current != NULL){
        stmt_table(current);
        current = current->next;
    }
}

void stmt_table(struct stmt_node* stmt) {
    switch (stmt->type) {
        case expr:

            break;

        case declaration:

            break;

        case let:

            break;

        default:
            break;
    }
}

void declaration_stmt_table(struct decl_stmt_node* node) {
    switch (node->type) {
        case enum_:
            enum_stmt_table(node->enum_item);
            break;
        case function_:

            break;
        case struct_:

            break;
        case constStmt_:

            break;
        case trait_:

            break;
        case impl_:

            break;
        default:
            break;
    }
}

//void expr_node(struct expr_node* expr) {
//    switch (expr->type) {
//        case id:
//            break;
//        case :
//        default:
//            break;
//    }
//}


void enum_stmt_table(struct enum_node* enum_node) {
    struct table_item* item = searchByString(table, enum_node->name);
    if (item == NULL) {
        struct table_item* utf8_item = createRecord(Utf8, enum_node->name, null, null);
        struct table_item* class_item = createRecord(Class, NULL, utf8_item->ID, null);

    } else {

    }
}
void enum_items_table(struct table_item* class_item, struct  enum_node* enum_node) {
    struct enum_item_node* enum_item = enum_node->items->first;
    while (enum_item->next != NULL) {
        struct table_item* utf8_item = createRecord(Utf8, enum_item->name, null, null);
        if (enum_item->expr != NULL) {

        }
    }
}
