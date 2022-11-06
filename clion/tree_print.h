#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "nodes.h"

FILE *fp;
char * filename = "";
char global_buffer[100];
char name_buffer[100];

void declaration_print(int ID, char *name);
void function_print(struct function_node *func);
void connection_print(int parent_ID, int child_ID);
void expr_print(struct expr_node *expr);
void function_params_print(struct function_params_node *params);
void function_param_print(struct function_param_node *param);
void expr_list_print(struct expr_list_node *expr_list);
void stmt_print(struct stmt_node *stmt);
void stmt_list_print(struct stmt_list_node *stmt_list);
void decl_stmt_print(struct decl_stmt_node *decl_stmt);
void let_stmt_print(struct let_stmt_node *let_stmt);

int program_print(struct program_node *prg)
{
    if((fp = fopen(filename, "w")!=NULL)){
        fputs("digraph G {", fp);

        declaration_print(prg->ID, "program");
        connection_print(prg->ID, prg->main->ID);

        function_print(prg->main);

        fputs("}", fp);
        fclose(fp);
    }
    return 0;
}

void declaration_print(int ID, char *name){

    char buffer[100];
    char id_buffer[17];
    strcat(buffer, "id");
    strcat(buffer, itoa(ID, id_buffer, 10));
    strcat(buffer, "[label=\"");
    strcat(buffer, name);
    strcat(buffer, " id=");
    strcat(buffer, itoa(ID, id_buffer, 10));
    strcat(buffer, "\"");
    fputs(buffer, fp);
}

void connection_print(int parent_ID, int child_ID){

    char buffer[100];
    char id_buffer[17];
    strcat(buffer, "id");
    strcat(buffer, itoa(parent_ID, id_buffer, 10));
    strcat(buffer, "->id");
    id_buffer[0] = 0;
    strcat(buffer, itoa(child_ID, id_buffer, 10));
    fputs(buffer, fp);
}

void function_print(struct function_node *func){

    declaration_print(func->ID, func->name);

    if(func->params!=NULL){
        connection_print(func->ID, func->params->ID);
        function_params_print(func->params);
    }

    connection_print(func->ID, func->body->ID);
    expr_print(func->body);
}

void function_params_print(struct function_params_node *params){

    declaration_print(params->ID, "params");

    struct function_param_node *current = params->first;
    while(current!=NULL){
        connection_print(params->ID, current->ID);
        function_param_print(current);
        current = current->next;
    }
}

void function_param_print(struct function_param_node *param){

    declaration_print(param->ID, param->name);
}

void expr_print(struct expr_node *expr){
    switch (expr->type) {
        case plus:
            declaration_print(expr->ID, "+");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case minus:
            declaration_print(expr->ID, "-");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case div_expr:
            declaration_print(expr->ID, "/");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case mul:
            declaration_print(expr->ID, "-");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case equal:
            declaration_print(expr->ID, "==");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case not_equal:
            declaration_print(expr->ID, "!=");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case greater:
            declaration_print(expr->ID, ">");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case less:
            declaration_print(expr->ID, "<");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case greater_equal:
            declaration_print(expr->ID, ">=");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case less_equal:
            declaration_print(expr->ID, "<=");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case or:
            declaration_print(expr->ID, "||");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case and:
            declaration_print(expr->ID, "&&");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case asgn:
            declaration_print(expr->ID, "=");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case range_expr:
            declaration_print(expr->ID, "..");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case range_in_expr:
            declaration_print(expr->ID, "..=");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case index_expr:
            declaration_print(expr->ID, "Expr [Expr]");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case range_left:
            declaration_print(expr->ID, "Expr..");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            break;

        case range_right:
            declaration_print(expr->ID, "..Expr");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            break;

        case range_in_right:
            declaration_print(expr->ID, "..=Expr");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            break;

        case qt:
            declaration_print(expr->ID, "?");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            break;

        case uminus:
            declaration_print(expr->ID, "-Expr");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            break;

        case neg:
            declaration_print(expr->ID, "!Expr");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            break;

        case break_expr:
            declaration_print(expr->ID, "break");
            if(expr->expr_left!=NULL){
                connection_print(expr->ID, expr->expr_left->ID);
                expr_print(expr->expr_left);
            }
            break;

        case return_expr:
            declaration_print(expr->ID, "return");
            if(expr->expr_left!=NULL){
                connection_print(expr->ID, expr->expr_left->ID);
                expr_print(expr->expr_left);
            }
            break;

        case continue_expr:
            declaration_print(expr->ID, "continue");
            break;

        case array_expr:
            declaration_print(expr->ID, "[Expr]");

            connection_print(expr->ID, expr->expr_list->ID);
            expr_list_print(expr->expr_list);
            break;

        case array_expr_auto_fill:
            declaration_print(expr->ID, "[Expr;Expr]");

            connection_print(expr->ID, expr->expr_list->ID);
            expr_list_print(expr->expr_list);
            break;

        case id:
            declaration_print(expr->ID, expr->Name);
            break;

        case call_expr:
            declaration_print(expr->ID, expr->Name);
            if(expr->expr_list!=NULL){
                connection_print(expr->ID, expr->expr_list->ID);
                expr_list_print(expr->expr_list);
            }
            break;

        case method_expr:
            declaration_print(expr->ID, expr->Name);
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_list->ID);
            expr_list_print(expr->expr_list);
            break;

        case field_access_expr:
            declaration_print(expr->ID, expr->Name);
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            break;

        case if_expr:
            declaration_print(expr->ID, "if");
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);

            connection_print(expr->ID, expr->body->ID);
            expr_print(expr->body);

            connection_print(expr->ID, expr->body->ID);
            expr_print(expr->else_body);
            break;

        case loop_expr:
            declaration_print(expr->ID, "loop");
            connection_print(expr->ID, expr->body->ID);
            expr_print(expr->body);
            break;

        case loop_for:
            name_buffer[0] = 0;
            strcat(name_buffer, "for ");
            strcat(name_buffer, expr->Name);
            declaration_print(expr->ID, name_buffer);
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);

            connection_print(expr->ID, expr->body->ID);
            expr_print(expr->body);
            break;

        case loop_while:
            declaration_print(expr->ID, "while");
            connection_print(expr->ID, expr->expr_left->ID);
            break;

        case block_expr:
            declaration_print(expr->ID, "body");
            if (expr->stmt_list!=NULL){
                connection_print(expr->ID, expr->stmt_list->ID);
                stmt_list_print(expr->stmt_list);
            }
            break;

        case int_lit:
            declaration_print(expr->ID, "int_lit");
            break;

        case float_lit:
            declaration_print(expr->ID, "float_int");
            break;

        case bool_lit:
            declaration_print(expr->ID, "bool_lit");
            break;

        case char_lit:
            declaration_print(expr->ID, "char_lit");
            break;

        case string_lit:
            declaration_print(expr->ID, "string_lit");
            break;
    }
}

void expr_list_print(struct expr_list_node *expr_list){

    declaration_print(expr_list->ID, "expr_list");

    struct expr_node *current = expr_list->first;
    while(current!=NULL){
        connection_print(expr_list->ID, current->ID);
        expr_print(current);
        current = current->next;
    }
}

void stmt_print(struct stmt_node *stmt){
    switch (stmt->type) {
        case semicolon:
            declaration_print(stmt->ID, ";");
            break;

        case expr_stmt:
            declaration_print(stmt->ID, "expr_stmt");
            connection_print(stmt->ID, stmt->expr->ID);
            expr_print(stmt->expr);
            break;

        case declaration:
            declaration_print(stmt->ID, "declaration_stmt");
            connection_print(stmt->ID, stmt->decl_stmt->ID);
            decl_stmt_print(stmt->decl_stmt);
            break;

        case let:
            declaration_print(stmt->ID, "let_stmt");
            connection_print(stmt->ID, stmt->let_stmt->ID);
            let_stmt_print(stmt->let_stmt);
            break;
    }
}

void stmt_list_print(struct stmt_list_node *stmt_list){

}

void decl_stmt_print(struct decl_stmt_node *decl_stmt){

}

void let_stmt_print(struct let_stmt_node *let_stmt){

}