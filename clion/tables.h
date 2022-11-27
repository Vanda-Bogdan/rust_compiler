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


//-----Tree-------

void stmt_list_table(struct stmt_list_node *stmt_list);

int tree_make_table(struct program_node *prg){

    stmt_list_table(prg->stmt_list);

    return 0;
}

void stmt_list_table(struct stmt_list_node *stmt_list){

}