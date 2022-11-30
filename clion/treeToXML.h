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
            fprintf(xml, "<expr type=\"STRUCT_EXPR\" ident=\"%s\">\n", expr->Name);
            if(expr->expr_list!=NULL){
                expr_list_xml(expr->expr_list);
            }
            fprintf(xml, "</expr>\n");
            break;

        case struct_field_expr:
            fprintf(xml, "<expr type=\"STRUCT_FIELD_EXPR\" ident=\"%s\">\n", expr->Name);
            expr_xml(expr->expr_left);
            fprintf(xml, "</expr>\n");
            break;
    }
}

void decl_stmt_xml(struct decl_stmt_node *decl_stmt){

    char visibility[20];
    visibility[0] = 0;
    switch (decl_stmt->visibility) {
        case pub:
            strcat(visibility, "pub");
            break;
        case crate:
            strcat(visibility, "crate");
            break;
        case self:
            strcat(visibility, "self");
            break;
        case super:
            strcat(visibility, "super");
            break;
        case emptyVisibility:
            strcat(visibility, "default");
            break;
    }

    switch (decl_stmt->type) {
        case enum_:
            fprintf(xml, "<decl_stmt type=\"ENUM_STMT\" visib=\"%s\">\n", visibility);
            enum_xml(decl_stmt->enum_item);
            fprintf(xml, "</decl_stmt>\n");
            break;

        case function_:
            fprintf(xml, "<decl_stmt type=\"FUNCTION_STMT\" visib=\"%s\">\n", visibility);
            function_xml(decl_stmt->function_item);
            fprintf(xml, "</decl_stmt>\n");
            break;

        case constStmt_:
            fprintf(xml, "<decl_stmt type=\"CONST_STMT\" visib=\"%s\">\n", visibility);
            const_stmt_xml(decl_stmt->const_stmt_item);
            fprintf(xml, "</decl_stmt>\n");
            break;

        case struct_:
            fprintf(xml, "<decl_stmt type=\"STRUCT_STMT\" visib=\"%s\">\n", visibility);
            struct_xml(decl_stmt->struct_item);
            fprintf(xml, "</decl_stmt>\n");
            break;

        case trait_:
            fprintf(xml, "<decl_stmt type=\"TRAIT_STMT\" visib=\"%s\">\n", visibility);
            trait_xml(decl_stmt->trait_item);
            fprintf(xml, "</decl_stmt>\n");
            break;

        case impl_:
            fprintf(xml, "<decl_stmt type=\"IMPL_STMT\" visib=\"%s\">\n", visibility);
            impl_xml(decl_stmt->impl_item);
            fprintf(xml, "</decl_stmt>\n");
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

void enum_xml(struct enum_node *enum_node){

    fprintf(xml, "<enum ident=\"%s\">\n", enum_node->name);
    if(enum_node->items!=NULL){
        enum_list_xml(enum_node->items);
    }
    fprintf(xml, "</enum>\n");
}

void enum_list_xml(struct enum_list_node *enum_list){

    struct enum_item_node *current = enum_list->first;

    fprintf(xml, "<enum_list>\n");
    while(current!=NULL){
        enum_item_xml(current);
        current = current->next;
    }
    fprintf(xml, "</enum_list>\n");
}

void enum_item_xml(struct enum_item_node *enum_item){
    char visibility[20];
    visibility[0] = 0;
    switch (enum_item->visibility) {
        case pub:
            strcat(visibility, "pub");
            break;
        case crate:
            strcat(visibility, "crate");
            break;
        case self:
            strcat(visibility, "self");
            break;
        case super:
            strcat(visibility, "super");
            break;
        case emptyVisibility:
            strcat(visibility, "default");
            break;
    }

    fprintf(xml, "<enum_item visib=\"%s\" ident=\"%s\">\n", visibility, enum_item->name);
    if(enum_item->struct_list!=NULL){
        struct_items_xml(enum_item->struct_list);
    }
    if(enum_item->expr!=NULL){
        expr_xml(enum_item->expr);
    }
    fprintf(xml, "</enum_item>\n");
}

void function_xml(struct function_node *func){
    fprintf(xml, "<func_node ident=\"%s\">\n", func->name);
    type_xml(func->returnType);
    if(func->params!=NULL){
        function_params_xml(func->params);
    }
    if(func->body!=NULL){
        expr_xml(func->body);
    }
    fprintf(xml, "</func_node>\n");
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

    fprintf(xml, "<func_params func_type=\"%s\">\n", func_type);
    while(current!=NULL){
        function_param_xml(current);
        current = current->next;
    }
    fprintf(xml, "</func_params>\n");
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

    fprintf(xml, "<func_param ident=\"%s\" mutability=\"%s\">\n", param->name, mutability);
    type_xml(param->type);
    fprintf(xml, "</func_param>\n");
}

void const_stmt_xml(struct const_stmt_node *const_stmt){
    fprintf(xml, "<const_stmt ident=\"%s\">\n", const_stmt->name);
    type_xml(const_stmt->type);
    if(const_stmt->expr!=NULL){
        expr_xml(const_stmt->expr);
    }
    fprintf(xml, "</const_stmt>\n");
}


void struct_xml(struct struct_node *struct_node){
    fprintf(xml, "<struct ident=\"%s\">\n", struct_node->name);
    if(struct_node->items!=NULL){
        struct_items_xml(struct_node->items);
    }
    fprintf(xml, "</struct>\n");
}
void struct_items_xml(struct struct_list_node *struct_items){
    fprintf(xml, "<struct_items>\n");
    struct struct_item_node *current = struct_items->first;
    while(current!=NULL){
        struct_item_xml(current);
        current = current->next;
    }
    fprintf(xml, "</struct_items>\n");
}

void struct_item_xml(struct struct_item_node *struct_item){
    char visibility[20];
    visibility[0] = 0;
    switch (struct_item->visibility) {
        case pub:
            strcat(visibility, "pub");
            break;
        case crate:
            strcat(visibility, "crate");
            break;
        case self:
            strcat(visibility, "self");
            break;
        case super:
            strcat(visibility, "super");
            break;
        case emptyVisibility:
            strcat(visibility, "default");
            break;
    }

    fprintf(xml, "<struct_item visib=\"%s\" ident=\"%s\">\n", visibility, struct_item->name);
    type_xml(struct_item->type);
    fprintf(xml, "</struct_item>\n");
}

void trait_xml(struct trait_node *trait_node){
    fprintf(xml, "<trait_node ident=\"%s\">\n", trait_node->name);
    if(trait_node->items!=NULL){
        associated_items_xml(trait_node->items);
    }
    fprintf(xml, "</trait_node>\n");
}

void associated_items_xml(struct associated_items_node *items){
    fprintf(xml, "<associated_items>\n");
    if(items->first!=NULL){
        struct associated_item_node *current = items->first;
        while(current!=NULL){
            associated_item_xml(current);
            current = current->next;
        }
    }
    fprintf(xml, "</associated_items>\n");
}

void associated_item_xml(struct associated_item_node *item){
    char visibility[20];
    visibility[0] = 0;
    switch (item->visibility) {
        case pub:
            strcat(visibility, "pub");
            break;
        case crate:
            strcat(visibility, "crate");
            break;
        case self:
            strcat(visibility, "self");
            break;
        case super:
            strcat(visibility, "super");
            break;
        case emptyVisibility:
            strcat(visibility, "default");
            break;
    }

    if(item->fn!=NULL){
        fprintf(xml, "<associated_item type=\"FUNCTION\" visib=\"%s\">\n", visibility);
        function_xml(item->fn);
    }
    if(item->const_stmt!=NULL){
        fprintf(xml, "<associated_item type=\"CONST_ITEM\" visib=\"%s\">\n", visibility);
        const_stmt_xml(item->const_stmt);
    }
    fprintf(xml, "</associated_item>\n");
}

void impl_xml(struct impl_node *impl_node){
    char impl_type[20];
    impl_type[0] = 0;
    switch (impl_node->implType) {
        case inherent:
            strcat(impl_type, "inherent");
            break;
        case trait:
            strcat(impl_type, "trait");
            break;
    }

    if(impl_node->name!=NULL){
        fprintf(xml, "impl_node type=\"%s\" name=\"%s\">\n", impl_type, impl_node->name);
    }else{
        fprintf(xml, "<impl_node type=\"%s\">\n", impl_type);
    }

    type_xml(impl_node->type);

    if(impl_node->items!=NULL){
        associated_items_xml(impl_node->items);
    }
    fprintf(xml, "</impl_node>\n");
}

void type_xml(struct type_node *type_node){
    fprintf(xml, "<type_node type=\"%s\">\n", type(type_node->type));

    if(type_node->type==array_){
        type_xml(type_node->typeArr);
    }
    fprintf(xml, "</type_node>\n");
}