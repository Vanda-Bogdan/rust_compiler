#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "nodes.h"

FILE *xml;
char * filenameXML = "treeXML.xml";
char name_buffer[50];

void stmt_list_xml(struct stmt_list_node *stmt_list);
void stmt_xml(struct stmt_node *stmt);
void expr_xml(struct expr_node *expr);
void decl_stmt_xml(struct decl_stmt_node *decl_stmt);
void let_stmt_xml(struct let_stmt_node *let_stmt);
void expr_list_xml(struct expr_list_node *expr_list);

int program_xml(struct program_node *prg)
{
    if((xml = fopen(filenameXML, "w"))){
        fprintf(xml, "<?xml version=\"1.0\"?>\n");
        fprintf(xml, "<program>\n");
        stmt_list_xml(prg->stmt_list);
        fprintf(xml, "</program>\n");

        fclose(xml);
    }
    return 0;
}

void stmt_list_xml(struct stmt_list_node *stmt_list){


    struct stmt_node *current = stmt_list->first;

    fprintf(xml, "<stmt_list>\n");
    while(current!=NULL){
        stmt_xml(current);
        current = current->next;
    }
    fprintf(xml, "</stmt_list>\n");
}

void stmt_xml(struct stmt_node *stmt){
    switch (stmt->type) {
        case semicolon:
            fprintf(xml, "<semicolon/>\n");
            break;

        case expr:
            fprintf(xml, "<expr_stmt>\n");
            expr_xml(stmt->expr);
            fprintf(xml, "</expr_stmt>\n");
            break;

        case declaration:
            fprintf(xml, "<declaration_stmt>\n");
            decl_stmt_xml(stmt->decl_stmt);
            fprintf(xml, "</declaration_stmt>\n");
            break;

        case let:
            fprintf(xml, "<let_stmt>\n");
            let_stmt_xml(stmt->let_stmt);
            fprintf(xml, "</let_stmt>\n");
            break;
    }
}

void expr_xml(struct expr_node *expr){
    switch (expr->type) {
        case plus:
            fprintf(xml, "<expr type=\"PLUS\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case minus:
            fprintf(xml, "<expr type=\"MINUS\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case div_expr:
            fprintf(xml, "<expr type=\"DIV_EXPR\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case mul:
            fprintf(xml, "<expr type=\"MUL\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case equal:
            fprintf(xml, "<expr type=\"EQUAL\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case not_equal:
            fprintf(xml, "<expr type=\"NOT_EQUAL\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case greater:
            fprintf(xml, "<expr type=\"GREATER\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case less:
            fprintf(xml, "<expr type=\"LESS\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case greater_equal:
            fprintf(xml, "<expr type=\"GREATER_EQUAL\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case less_equal:
            fprintf(xml, "<expr type=\"LESS_EQUAL\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case or:
            fprintf(xml, "<expr type=\"OR\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case and:
            fprintf(xml, "<expr type=\"AND\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case asgn:
            fprintf(xml, "<expr type=\"ASGN\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case range_expr:
            fprintf(xml, "<expr type=\"RANGE_EXPR\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case range_in_expr:
            fprintf(xml, "<expr type=\"RANGE_IN_EXPR\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case index_expr:
            fprintf(xml, "<expr type=\"INDEX_EXPR\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case range_left:
            fprintf(xml, "<expr type=\"RANGE_LEFT\">\n");
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;

        case range_right:
            fprintf(xml, "<expr type=\"RANGE_RIGHT\">\n");
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;

        case range_in_right:
            fprintf(xml, "<expr type=\"RANGE_IN_RIGHT\">\n");
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;

        case qt:
            fprintf(xml, "<expr type=\"QT\">\n");
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;

        case uminus:
            fprintf(xml, "<expr type=\"UMINUS\">\n");
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;

        case neg:
            fprintf(xml, "<expr type=\"NEG\">\n");
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;

        case break_expr:
            fprintf(xml, "<expr type=\"BREAK_EXPR\">\n");
            if(expr->expr_left!=NULL){
                expr_xml(expr->expr_left);
            }
            fprintf(xml, "</expr>\n");
            break;

        case return_expr:
            fprintf(xml, "<expr type=\"RETURN_EXPR\">\n");
            if(expr->expr_left!=NULL){
                expr_xml(expr->expr_left);
            }
            fprintf(xml, "</expr>\n");
            break;

        case continue_expr:
            fprintf(xml, "<expr type=\"CONTINUE_EXPR\"/>\n");
            break;

        case array_expr:
            fprintf(xml, "<expr type=\"ARRAY_EXPR\">\n");
            expr_list_xml(expr->expr_list);
            fprintf(xml, "</expr>\n");
            break;

        case array_expr_auto_fill:
            fprintf(xml, "<expr type=\"ARRAY_AUTO_FILL_EXPR\">\n");
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>\n");
            break;

        case id:
            fprintf(xml, "<expr type=\"ID\" ident=\"%s\"/>\n", expr->Name);
            break;

        case self_expr:
            fprintf(xml, "<expr type=\"SELF_EXPR\"/>\n");
            break;

        case call_expr:
            fprintf(xml, "<expr type=\"CALL_EXPR\" ident=\"%s\">\n", expr->Name);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>\n");
            break;

        case method_expr:
            fprintf(xml, "<expr type=\"METHOD_EXPR\" ident=\"%s\">\n", expr->Name);
            expr_xml(expr->expr_left);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>\n");
            break;

        case static_method:
            fprintf(xml, "<expr type=\"STATIC_METHOD\" ident=\"%s\" parent_ident=\"%s\">\n", expr->Name, expr->ParentID);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>\n");
            break;

        case field_access_expr:
            fprintf(xml, "<expr type=\"FIELD_ACCESS_EXPR\" ident=\"%s\">\n", expr->Name);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;

        case if_expr:
            fprintf(xml, "<expr type=\"IF_EXPR\">\n");

            expr_xml(expr->expr_left);
            expr_xml(expr->body);

            if(expr->else_body!=NULL){
                expr_xml(expr->else_body);
            }
            fprintf(xml, "</expr>\n");
            break;

        case loop_expr:
            fprintf(xml, "<expr type=\"LOOP_EXPR\">\n");
            expr_xml(expr->body);
            fprintf(xml, "</expr>\n");
            break;

        case loop_for:
            fprintf(xml, "<expr type=\"LOOP_FOR_EXPR\" ident=\"%s\">\n", expr->Name);
            expr_xml(expr->expr_left);
            expr_xml(expr->body);
            fprintf(xml, "</expr>\n");
            break;

        case loop_while:
            fprintf(xml, "<expr type=\"LOOP_WHILE_EXPR\">\n");
            expr_xml(expr->expr_left);
            if(expr->body!=NULL){
                expr_xml(expr->body);
            }
            fprintf(xml, "</expr>\n");
            break;

        case block_expr:
            fprintf(xml, "<expr type=\"BLOCK_EXPR\">\n");
            if (expr->stmt_list!=NULL){
                stmt_list_xml(expr->stmt_list);
            }
            fprintf(xml, "</expr>\n");
            break;

        case int_lit:
            fprintf(xml, "<expr type=\"INT_LIT\" value=\"%d\"/>\n", expr->Int);
            break;

        case float_lit:
            fprintf(xml, "<expr type=\"FLOAT_LIT\" value=\"%f\"/>\n", expr->Float);
            break;

        case bool_lit:
            if(expr->Bool){
                fprintf(xml, "<expr type=\"BOOL_LIT\" value=\"true\"/>\n");
            }
            else{
                fprintf(xml, "<expr type=\"BOOL_LIT\" value=\"false\"/>\n");
            }
            break;

        case char_lit:
            fprintf(xml, "<expr type=\"FLOAT_LIT\" value=\"%c\"/>\n", expr->Char);
            break;

        case string_lit:
            fprintf(xml, "<expr type=\"STRING_LIT\"><![CDATA[%s]]></expr>\n", expr->String);
            break;

        case struct_expr:
            fprintf(xml, "<expr type=\"STRUCT_EXPR\" ident=\"%s\"/>\n", expr->Name);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>\n");
            break;

        case struct_field_expr:
            fprintf(xml, "<expr type=\"STRUCT_FIELD_EXPR\" ident=\"%s\"/>\n", expr->Name);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;
    }
}

void decl_stmt_xml(struct decl_stmt_node *decl_stmt){
    switch (decl_stmt->type) {
        case enum_:
            declaration_print2(decl_stmt->ID, visibility, "enum");
            connection_print(decl_stmt->ID, decl_stmt->enum_item->ID);
            enum_print(decl_stmt->enum_item);
            break;

        case function_:
            declaration_print2(decl_stmt->ID, visibility, "function");
            connection_print(decl_stmt->ID, decl_stmt->function_item->ID);
            function_print(decl_stmt->function_item);
            break;

        case constStmt_:
            declaration_print2(decl_stmt->ID, visibility, "const_stmt");
            connection_print(decl_stmt->ID, decl_stmt->const_stmt_item->ID);
            const_stmt_print(decl_stmt->const_stmt_item);
            break;

        case struct_:
            declaration_print2(decl_stmt->ID, visibility,"struct");
            connection_print(decl_stmt->ID, decl_stmt->struct_item->ID);
            struct_print(decl_stmt->struct_item);
            break;

        case trait_:
            declaration_print2(decl_stmt->ID, visibility,"trait");
            connection_print(decl_stmt->ID, decl_stmt->trait_item->ID);
            trait_print(decl_stmt->trait_item);
            break;

        case impl_:
            declaration_print2(decl_stmt->ID, visibility,"impl");
            connection_print(decl_stmt->ID, decl_stmt->impl_item->ID);
            impl_print(decl_stmt->impl_item);
            break;
    }
}

void let_stmt_xml(struct let_stmt_node *let_stmt){

}

void expr_list_xml(struct expr_list_node *expr_list){

    struct expr_node *current = expr_list->first;

    fprintf(xml, "<expr_list>\n");
    while(current!=NULL){
        expr_xml(current);
        current = current->next;
    }
    fprintf(xml, "</expr_list>\n");

}