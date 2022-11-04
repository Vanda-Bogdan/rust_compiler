#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "nodes.h"

FILE *fp;
char * filename = "";
char global_buffer[100];

void declaration_print(int ID, char *name, char *buffer);
void function_print(struct function_node *func);
void connection_print(int parent_ID, int child_ID, char *buffer);

int program_print(struct program_node *prg)
{
    if((fp = fopen(filename, "w")!=NULL)){
        fputs("digraph G {", fp);

        declaration_print(prg->ID, "program", global_buffer);
        fputs(global_buffer, fp);
        connection_print(prg->ID, prg->main->ID);
        fputs(global_buffer, fp);

        function_print(prg->main);

        fputs("}", fp);
        fclose(fp);
    }
    return 0;
}

void declaration_print(int ID, char *name, char *buffer){

    buffer[0] = 0;
    char id_buffer[17];
    strcat(buffer, "id");
    strcat(buffer, itoa(ID, id_buffer, 10));
    strcat(buffer, "[label=\"");
    strcat(buffer, name);
    strcat(buffer, " id=");
    strcat(buffer, itoa(ID, id_buffer, 10));
}

void connection_print(int parent_ID, int child_ID, char *buffer){

    buffer[0] = 0;
    char id_buffer[17];
    strcat(buffer, "id");
    strcat(buffer, itoa(parent_ID, id_buffer, 10));
    strcat(buffer, "->id");
    id_buffer[0] = 0;
    strcat(buffer, itoa(child_ID, id_buffer, 10));
}

void function_print(struct function_node *func){

}