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
void enum_xml(struct enum_node *enum_node);
void enum_list_xml(struct enum_list_node *enum_list);
void enum_item_xml(struct enum_item_node *enum_item);
void function_xml(struct function_node *func);
void function_params_xml(struct function_params_node *params);
void function_param_xml(struct function_param_node *param);
void const_stmt_xml(struct const_stmt_node *const_stmt);
void struct_xml(struct struct_node *struct_node);
void struct_items_xml(struct struct_list_node *struct_items);
void struct_item_xml(struct struct_item_node *struct_item);
void trait_xml(struct trait_node *trait_node);
void associated_items_xml(struct associated_items_node *items);
void associated_item_xml(struct associated_item_node *item);
void impl_xml(struct impl_node *impl_node);
void type_xml(struct type_node *type_node);


int program_xml(struct program_node *prg)
{
    if((xml = fopen(filenameXML, "w"))){
        fprintf(xml, "<?xml version=\"1.0\"?>");
        fprintf(xml, "<program ID=\"%d\">", prg->ID);
        stmt_list_xml(prg->stmt_list);
        fprintf(xml, "</program>");

        fclose(xml);
    }
    return 0;
}

void stmt_list_xml(struct stmt_list_node *stmt_list){
    struct stmt_node *current = stmt_list->first;

    fprintf(xml, "<stmt_list ID=\"%d\">", stmt_list->ID);
    while(current!=NULL){
        stmt_xml(current);
        current = current->next;
    }
    fprintf(xml, "</stmt_list>");
}

void stmt_xml(struct stmt_node *stmt){
    switch (stmt->type) {
        case semicolon:
            fprintf(xml, "<stmt type=\"SEMICOLON\" ID=\"%d\"/>", stmt->ID);
            break;

        case expr:
            fprintf(xml, "<stmt type=\"EXPRESSION\" ID=\"%d\">", stmt->ID);
            expr_xml(stmt->expr);
            fprintf(xml, "</stmt>");
            break;

        case declaration:
            fprintf(xml, "<stmt type=\"DECLARATION\" ID=\"%d\">", stmt->ID);
            decl_stmt_xml(stmt->decl_stmt);
            fprintf(xml, "</stmt>");
            break;

        case let:
            fprintf(xml, "<stmt type=\"LET\" ID=\"%d\">", stmt->ID);
            let_stmt_xml(stmt->let_stmt);
            fprintf(xml, "</stmt>");
            break;
    }
}

void expr_xml(struct expr_node *expr){
    switch (expr->type) {
        case plus:
            fprintf(xml, "<expr type=\"PLUS\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case minus:
            fprintf(xml, "<expr type=\"MINUS\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case div_expr:
            fprintf(xml, "<expr type=\"DIV\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case mul:
            fprintf(xml, "<expr type=\"MUL\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case equal:
            fprintf(xml, "<expr type=\"EQUAL\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case not_equal:
            fprintf(xml, "<expr type=\"NOT_EQUAL\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case greater:
            fprintf(xml, "<expr type=\"GREATER\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case less:
            fprintf(xml, "<expr type=\"LESS\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case greater_equal:
            fprintf(xml, "<expr type=\"GREATER_EQUAL\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case less_equal:
            fprintf(xml, "<expr type=\"LESS_EQUAL\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case or:
            fprintf(xml, "<expr type=\"OR\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case and:
            fprintf(xml, "<expr type=\"AND\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case asgn:
            fprintf(xml, "<expr type=\"ASGN\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case range_expr:
            fprintf(xml, "<expr type=\"RANGE\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case range_in_expr:
            fprintf(xml, "<expr type=\"RANGE_IN\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case index_expr:
            fprintf(xml, "<expr type=\"INDEX\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case range_left:
            fprintf(xml, "<expr type=\"RANGE_LEFT\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;

        case range_right:
            fprintf(xml, "<expr type=\"RANGE_RIGHT\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;

        case range_in_right:
            fprintf(xml, "<expr type=\"RANGE_IN_RIGHT\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;

        case qt:
            fprintf(xml, "<expr type=\"QT\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;

        case uminus:
            fprintf(xml, "<expr type=\"U_MINUS\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;

        case neg:
            fprintf(xml, "<expr type=\"NEG\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;

        case break_expr:
            fprintf(xml, "<expr type=\"BREAK\" ID=\"%d\">", expr->ID);
            if(expr->expr_left!=NULL){
                expr_xml(expr->expr_left);
            }
            fprintf(xml, "</expr>");
            break;

        case return_expr:
            fprintf(xml, "<expr type=\"RETURN\" ID=\"%d\">", expr->ID);
            if(expr->expr_left!=NULL){
                expr_xml(expr->expr_left);
            }
            fprintf(xml, "</expr>");
            break;

        case continue_expr:
            fprintf(xml, "<expr type=\"CONTINUE\" ID=\"%d\"/>", expr->ID);
            break;

        case array_expr:
            fprintf(xml, "<expr type=\"ARRAY\" ID=\"%d\">", expr->ID);
            expr_list_xml(expr->expr_list);
            fprintf(xml, "</expr>");
            break;

        case array_expr_auto_fill:
            fprintf(xml, "<expr type=\"ARRAY_AUTO_FILL\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->expr_right);
            fprintf(xml, "</expr>");
            break;

        case id:
            fprintf(xml, "<expr type=\"ID\" ident=\"%s\" ID=\"%d\"/>", expr->Name, expr->ID);
            break;

        case self_expr:
            fprintf(xml, "<expr type=\"SELF\" ident=\"self\" ID=\"%d\"/>", expr->ID);
            break;

        case call_expr:
            fprintf(xml, "<expr type=\"CALL\" ident=\"%s\" ID=\"%d\">", expr->Name, expr->ID);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>");
            break;

        case method_expr:
            fprintf(xml, "<expr type=\"METHOD\" ident=\"%s\" ID=\"%d\">", expr->Name, expr->ID);
            expr_xml(expr->expr_left);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>");
            break;

        case static_method:
            fprintf(xml, "<expr type=\"STATIC_METHOD\" ident=\"%s\" parent_ident=\"%s\" ID=\"%d\">", expr->Name, expr->ParentID, expr->ID);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>");
            break;

        case field_access_expr:
            fprintf(xml, "<expr type=\"FIELD_ACCESS\" ident=\"%s\" ID=\"%d\">", expr->Name, expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;

        case if_expr:
            fprintf(xml, "<expr type=\"IF\" ID=\"%d\">", expr->ID);

            expr_xml(expr->expr_left);
            expr_xml(expr->body);

            if(expr->else_body!=NULL){
                expr_xml(expr->else_body);
            }
            fprintf(xml, "</expr>");
            break;

        case loop_expr:
            fprintf(xml, "<expr type=\"LOOP\" ID=\"%d\">", expr->ID);
            expr_xml(expr->body);
            fprintf(xml, "</expr>");
            break;

        case loop_for:
            fprintf(xml, "<expr type=\"LOOP_FOR\" ident=\"%s\" ID=\"%d\">", expr->Name, expr->ID);
            expr_xml(expr->expr_left);
            expr_xml(expr->body);
            fprintf(xml, "</expr>");
            break;

        case loop_while:
            fprintf(xml, "<expr type=\"LOOP_WHILE\" ID=\"%d\">", expr->ID);
            expr_xml(expr->expr_left);
            if(expr->body!=NULL){
                expr_xml(expr->body);
            }
            fprintf(xml, "</expr>");
            break;

        case block_expr:
            fprintf(xml, "<expr type=\"BLOCK\" ID=\"%d\">", expr->ID);
            if (expr->stmt_list!=NULL){
                stmt_list_xml(expr->stmt_list);
            }
            fprintf(xml, "</expr>");
            break;

        case int_lit:
            fprintf(xml, "<expr type=\"INT_LIT\" value=\"%d\" ID=\"%d\"/>", expr->Int, expr->ID);
            break;

        case float_lit:
            fprintf(xml, "<expr type=\"FLOAT_LIT\" value=\"%f\" ID=\"%d\"/>", expr->Float, expr->ID);
            break;

        case bool_lit:
            if(expr->Bool){
                fprintf(xml, "<expr type=\"BOOL_LIT\" value=\"true\" ID=\"%d\"/>", expr->ID);
            }
            else{
                fprintf(xml, "<expr type=\"BOOL_LIT\" value=\"false\" ID=\"%d\"/>", expr->ID);
            }
            break;

        case char_lit:
            fprintf(xml, "<expr type=\"CHAR_LIT\" value=\"%c\" ID=\"%d\"/>", expr->Char, expr->ID);
            break;

        case string_lit:
            fprintf(xml, "<expr type=\"STRING_LIT\" ID=\"%d\"><![CDATA[%s]]></expr>", expr->ID, expr->String);
            break;

        case struct_expr:
            fprintf(xml, "<expr type=\"STRUCT\" ident=\"%s\" ID=\"%d\">", expr->Name, expr->ID);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>");
            break;

        case struct_field_expr:
            fprintf(xml, "<expr type=\"STRUCT_FIELD\" ident=\"%s\" ID=\"%d\">", expr->Name, expr->ID);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>");
            break;
    }
}

void decl_stmt_xml(struct decl_stmt_node *decl_stmt){
    
    switch (decl_stmt->type) {
        case enum_:
            fprintf(xml, "<decl_stmt type=\"ENUM\"  ID=\"%d\">", decl_stmt->ID);
            enum_xml(decl_stmt->enum_item);
            fprintf(xml, "</decl_stmt>");
            break;

        case function_:
            fprintf(xml, "<decl_stmt type=\"FUNCTION\"  ID=\"%d\">",  decl_stmt->ID);
            function_xml(decl_stmt->function_item);
            fprintf(xml, "</decl_stmt>");
            break;

        case constStmt_:
            fprintf(xml, "<decl_stmt type=\"CONST_STMT\"  ID=\"%d\">",  decl_stmt->ID);
            const_stmt_xml(decl_stmt->const_stmt_item);
            fprintf(xml, "</decl_stmt>");
            break;

        case struct_:
            fprintf(xml, "<decl_stmt type=\"STRUCT\"  ID=\"%d\">",  decl_stmt->ID);
            struct_xml(decl_stmt->struct_item);
            fprintf(xml, "</decl_stmt>");
            break;

        case trait_:
            fprintf(xml, "<decl_stmt type=\"TRAIT\"  ID=\"%d\">",  decl_stmt->ID);
            trait_xml(decl_stmt->trait_item);
            fprintf(xml, "</decl_stmt>");
            break;

        case impl_:
            fprintf(xml, "<decl_stmt type=\"IMPL\"  ID=\"%d\">",  decl_stmt->ID);
            impl_xml(decl_stmt->impl_item);
            fprintf(xml, "</decl_stmt>");
            break;
    }
}

void let_stmt_xml(struct let_stmt_node *let_stmt){
    char mutability[20];
    mutability[0] = 0;
    switch (let_stmt->mutable) {
        case notMut:
            strcat(mutability, "NOT_MUT");
            break;
        case mut:
            strcat(mutability, "MUT");
            break;
    }

    fprintf(xml, "<let_stmt ident=\"%s\" mutability=\"%s\" ID=\"%d\">", let_stmt->name, mutability, let_stmt->ID);
    type_xml(let_stmt->type);

    if(let_stmt->expr!=NULL){
        expr_xml(let_stmt->expr);
    }

    fprintf(xml, "</let_stmt>");
}

void expr_list_xml(struct expr_list_node *expr_list){

    struct expr_node *current = expr_list->first;

    fprintf(xml, "<expr_list ID=\"%d\">", expr_list->ID);
    while(current!=NULL){
        expr_xml(current);
        current = current->next;
    }
    fprintf(xml, "</expr_list>");

}

void enum_xml(struct enum_node *enum_node){

    fprintf(xml, "<enum ident=\"%s\" ID=\"%d\">", enum_node->name, enum_node->ID);
    if(enum_node->items!=NULL){
        enum_list_xml(enum_node->items);
    }
    fprintf(xml, "</enum>");
}

void enum_list_xml(struct enum_list_node *enum_list){

    struct enum_item_node *current = enum_list->first;

    fprintf(xml, "<enum_list ID=\"%d\">", enum_list->ID);
    while(current!=NULL){
        enum_item_xml(current);
        current = current->next;
    }
    fprintf(xml, "</enum_list>");
}

void enum_item_xml(struct enum_item_node *enum_item){
    
    fprintf(xml, "<enum_item  ident=\"%s\" ID=\"%d\">",  enum_item->name, enum_item->ID);
    if(enum_item->struct_list!=NULL){
        struct_items_xml(enum_item->struct_list);
    }
    if(enum_item->expr!=NULL){
        expr_xml(enum_item->expr);
    }
    fprintf(xml, "</enum_item>");
}

void function_xml(struct function_node *func){
    fprintf(xml, "<func_node ident=\"%s\" ID=\"%d\">", func->name, func->ID);
    type_xml(func->returnType);
    if(func->params!=NULL){
        function_params_xml(func->params);
    }
    if(func->body!=NULL){
        expr_xml(func->body);
    }
    fprintf(xml, "</func_node>");
}

void function_params_xml(struct function_params_node *params){
    char func_type[20];
    func_type[0] = 0;
    switch (params->funcType) {
        case method_self:
            strcat(func_type, "METHOD_SELF");
            break;
        case method_mut_self:
            strcat(func_type, "METHOD_MUT_SELF");
            break;
        case associated:
            strcat(func_type, "ASSOCIATED");
            break;
    }
    struct function_param_node *current = params->first;

    fprintf(xml, "<func_params type=\"%s\" ID=\"%d\">", func_type, params->ID);
    while(current!=NULL){
        function_param_xml(current);
        current = current->next;
    }
    fprintf(xml, "</func_params>");
}

void function_param_xml(struct function_param_node *param){
    char mutability[20];
    mutability[0] = 0;
    switch (param->mutable) {
        case notMut:
            strcat(mutability, "NOT_MUT");
            break;
        case mut:
            strcat(mutability, "MUT");
            break;
    }

    fprintf(xml, "<func_param ident=\"%s\" mutability=\"%s\" ID=\"%d\">", param->name, mutability, param->ID);
    type_xml(param->type);
    fprintf(xml, "</func_param>");
}

void const_stmt_xml(struct const_stmt_node *const_stmt){
    fprintf(xml, "<const_stmt ident=\"%s\" ID=\"%d\">", const_stmt->name, const_stmt->ID);
    type_xml(const_stmt->type);
    if(const_stmt->expr!=NULL){
        expr_xml(const_stmt->expr);
    }
    fprintf(xml, "</const_stmt>");
}


void struct_xml(struct struct_node *struct_node){
    fprintf(xml, "<struct ident=\"%s\" ID=\"%d\">", struct_node->name, struct_node->ID);
    if(struct_node->items!=NULL){
        struct_items_xml(struct_node->items);
    }
    fprintf(xml, "</struct>");
}
void struct_items_xml(struct struct_list_node *struct_items){
    fprintf(xml, "<struct_items ID=\"%d\">", struct_items->ID);
    struct struct_item_node *current = struct_items->first;
    while(current!=NULL){
        struct_item_xml(current);
        current = current->next;
    }
    fprintf(xml, "</struct_items>");
}

void struct_item_xml(struct struct_item_node *struct_item){
    
    fprintf(xml, "<struct_item  ident=\"%s\" ID=\"%d\">",  struct_item->name, struct_item->ID);
    type_xml(struct_item->type);
    fprintf(xml, "</struct_item>");
}

void trait_xml(struct trait_node *trait_node){
    fprintf(xml, "<trait_node ident=\"%s\" ID=\"%d\">", trait_node->name, trait_node->ID);
    if(trait_node->items!=NULL){
        associated_items_xml(trait_node->items);
    }
    fprintf(xml, "</trait_node>");
}

void associated_items_xml(struct associated_items_node *items){
    fprintf(xml, "<associated_items ID=\"%d\">", items->ID);
    if(items->first!=NULL){
        struct associated_item_node *current = items->first;
        while(current!=NULL){
            associated_item_xml(current);
            current = current->next;
        }
    }
    fprintf(xml, "</associated_items>");
}

void associated_item_xml(struct associated_item_node *item){
    
    if(item->fn!=NULL){
        fprintf(xml, "<associated_item type=\"FUNCTION\"  ID=\"%d\">",  item->ID);
        function_xml(item->fn);
    }
    if(item->const_stmt!=NULL){
        fprintf(xml, "<associated_item type=\"CONST_ITEM\"  ID=\"%d\">",  item->ID);
        const_stmt_xml(item->const_stmt);
    }
    fprintf(xml, "</associated_item>");
}

void impl_xml(struct impl_node *impl_node){
    char impl_type[20];
    impl_type[0] = 0;
    switch (impl_node->implType) {
        case inherent:
            strcat(impl_type, "INHERENT");
            break;
        case trait:
            strcat(impl_type, "TRAIT");
            break;
    }

    if(impl_node->name!=NULL){
        fprintf(xml, "<impl_node type=\"%s\" ident=\"%s\" ID=\"%d\">", impl_type, impl_node->name, impl_node->ID);
    }else{
        fprintf(xml, "<impl_node type=\"%s\" ID=\"%d\">", impl_type, impl_node->ID);
    }

    type_xml(impl_node->type);

    if(impl_node->items!=NULL){
        associated_items_xml(impl_node->items);
    }
    fprintf(xml, "</impl_node>");
}

void type_xml(struct type_node *type_node){

    if(type_node->name!=NULL){
        fprintf(xml, "<type_node type=\"%s\" ident=\"%s\" ID=\"%d\">", type(type_node->type), type_node->name, type_node->ID);
    }
    else{
        fprintf(xml, "<type_node type=\"%s\" ID=\"%d\">", type(type_node->type), type_node->ID);
    }

    if(type_node->type==array_){
        type_xml(type_node->typeArr);
    }
    fprintf(xml, "</type_node>");
}