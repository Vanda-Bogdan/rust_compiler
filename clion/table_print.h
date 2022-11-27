#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "nodes.h"
#include "tables.h"

FILE *fp;
char * tablename = "table.csv";
char buffer[50];

void table_item_print(struct table_item* item);
const char * constantName(enum constant constant);
char * valueString(struct item_value* value);

void table_print(struct table_item* table){
    if((fp = fopen(tablename, "w"))){

        fputs("Number,Type,Value;", fp);

        struct table_item* current = table;
        while(current!=NULL){
            table_item_print(current);
            current=table->next;
        }
    }
}

void table_item_print(struct table_item* item){
    fputs(itoa(item->ID, buffer, 10), fp);
    fputs(",", fp);
    fputs(constantName(item->type), fp);
    fputs(",", fp);
    fputs(valueString(item->value), fp);
}

char * valueString(struct item_value* value){
    if (strlen(value->string) != 0){
        return value->string;
    }
    else{
        buffer[0] = 0;
        char itoa_buf[10];

        strcat(buffer, itoa(value->first, itoa_buf,10));
        strcat(buffer, " ");
        if(value->first>0){
            itoa_buf[0] = 0;
            strcat(buffer, itoa(value->first, itoa_buf,10));
        }

        return buffer;
    }
}

const char * constantName(enum constant constant){
    switch (constant) {
        case Utf8:
            return "Utf8";
            break;
        case Class:
            return "Class";
            break;
        case Methodref:
            return "Methodref";
            break;
        case NameAndType;
            return "NameAndType";
            break;
        case Integer:
            return "Integer";
            break;
        case Float:
            return "Float";
            break;
        default:
            return "DEFAULT";
            break;
    }
}


