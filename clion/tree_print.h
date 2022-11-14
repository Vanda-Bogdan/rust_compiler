#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "nodes.h"

FILE *fp;
char * filename = "tree.txt";
char name_buffer[50];

void declaration_print(int ID, char *name);
void function_print(struct function_node *func);
void connection_print(int parent_ID, int child_ID);
char* type(enum type type);
void type_print(struct type_node *type_node);
void expr_print(struct expr_node *expr);
void function_params_print(struct function_params_node *params);
void function_param_print(struct function_param_node *param);
void expr_list_print(struct expr_list_node *expr_list);
void stmt_print(struct stmt_node *stmt);
void stmt_list_print(struct stmt_list_node *stmt_list);
void decl_stmt_print(struct decl_stmt_node *decl_stmt);
void let_stmt_print(struct let_stmt_node *let_stmt);
void enum_print(struct enum_node *enum_node);
void enum_list_print(struct enum_list_node *enum_list);
void enum_item_print(struct enum_item_node *enum_item);
void const_stmt_print(struct const_stmt_node *const_stmt);
void struct_print(struct struct_node *struct_node);
void struct_items_print(struct struct_list_node *struct_items);
void struct_item_print(struct struct_item_node *struct_item);
void trait_print(struct trait_node *trait_node);
void associated_items_print(struct associated_items_node *items);
void associated_item_print(struct associated_item_node *item);
void impl_print(struct impl_node *impl_node);

int program_print(struct program_node *prg)
{
    if((fp = fopen(filename, "w"))){
        fputs("digraph G {\n", fp);

        declaration_print(prg->ID, "program");
        connection_print(prg->ID, prg->stmt_list->ID);

        stmt_list_print(prg->stmt_list);

        fputs("}", fp);
        fclose(fp);
    }
    return 0;
}

void declaration_print(int ID, char *name){

    char buffer[200];
    buffer[0] = 0;
    char id_buffer[25];
    id_buffer[0] = 0;

    strcat(buffer, "id");
    strcat(buffer, itoa(ID, id_buffer, 10));
    strcat(buffer, "[label=\"");
    strcat(buffer, name);
    strcat(buffer, " id=");
    strcat(buffer, itoa(ID, id_buffer, 10));
    strcat(buffer, "\"]\n");
    fputs(buffer, fp);
}

void declaration_print2(int ID, char *type, char *name){

    char buffer[200];
    buffer[0] = 0;
    char id_buffer[25];
    id_buffer[0] = 0;

    strcat(buffer, "id");
    strcat(buffer, itoa(ID, id_buffer, 10));
    strcat(buffer, "[label=\"");
    strcat(buffer, type);
    strcat(buffer, " ");
    strcat(buffer, name);
    strcat(buffer, " id=");
    strcat(buffer, itoa(ID, id_buffer, 10));
    strcat(buffer, "\"]\n");
    fputs(buffer, fp);
}

void connection_print(int parent_ID, int child_ID){

    char buffer[100];
    buffer[0] = 0;
    char id_buffer[17];
    id_buffer[0] = 0;

    strcat(buffer, "id");
    strcat(buffer, itoa(parent_ID, id_buffer, 10));
    strcat(buffer, "->id");
    id_buffer[0] = 0;
    strcat(buffer, itoa(child_ID, id_buffer, 10));
    strcat(buffer, "\n");
    fputs(buffer, fp);
}

char* type(enum type type){
    switch (type) {
        case emptyType:
            return "emptyType";
        case int_:
            return "int";
        case char_:
            return "char";
        case string_:
            return "String";
        case float_:
            return "float";
        case bool_:
            return "bool";
        case id_:
            return "idType";
        case array_:
            return "arrayType";
    }
}

void type_print(struct type_node *type_node){
    declaration_print2(type_node->ID, "type:",type(type_node->type));
    if(type_node->typeArr!=NULL){
        connection_print(type_node->ID, type_node->typeArr->ID);
        type_print(type_node->typeArr);
    }
}

void function_print(struct function_node *func){

    declaration_print(func->ID, func->name);

    connection_print(func->ID, func->returnType->ID);
    type_print(func->returnType);

    if(func->params!=NULL){
        connection_print(func->ID, func->params->ID);
        function_params_print(func->params);
    }

    connection_print(func->ID, func->body->ID);
    expr_print(func->body);
}

void function_params_print(struct function_params_node *params){

    char func_type[20];
    func_type[0] = 0;
    switch (params->funcType) {
        case method_self:
            strcat(func_type, "method_self");
            break;
        case method_mut_self:
            strcat(func_type, "method_mut_self");
            break;
        case associated:
            strcat(func_type, "associated");
            break;
    }

    declaration_print2(params->ID, func_type,"params");

    struct function_param_node *current = params->first;
    while(current!=NULL){
        connection_print(params->ID, current->ID);
        function_param_print(current);
        current = current->next;
    }
}

void function_param_print(struct function_param_node *param){

    declaration_print(param->ID, param->name);
    connection_print(param->ID, param->type->ID);
    type_print(param->type);
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
            declaration_print(expr->ID, "*");
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

            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            connection_print(expr->ID, expr->expr_right->ID);
            expr_print(expr->expr_right);
            break;

        case id:
            declaration_print2(expr->ID, "identifier:",expr->Name);
            break;

        case self_expr:
            declaration_print2(expr->ID, "this:",expr->Name);
            break;

        case call_expr:
            declaration_print2(expr->ID, "call method:",expr->Name);
            if(expr->expr_list!=NULL){
                connection_print(expr->ID, expr->expr_list->ID);
                expr_list_print(expr->expr_list);
            }
            break;

        case method_expr:
            declaration_print2(expr->ID, "method:",expr->Name);
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
            if(expr->expr_list!=NULL){
                connection_print(expr->ID, expr->expr_list->ID);
                expr_list_print(expr->expr_list);
            }
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

            if(expr->else_body!=NULL){
                connection_print(expr->ID, expr->else_body->ID);
                expr_print(expr->else_body);
            }

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
            expr_print(expr->expr_left);
            if(expr->body!=NULL){
                connection_print(expr->ID, expr->body->ID);
                expr_print(expr->body);
            }
            break;

        case block_expr:
            declaration_print(expr->ID, "body");
            if (expr->stmt_list!=NULL){
                connection_print(expr->ID, expr->stmt_list->ID);
                stmt_list_print(expr->stmt_list);
            }
            break;

        case int_lit:
            name_buffer[0] = 0;
            declaration_print2(expr->ID, "int_lit:",  itoa(expr->Int,name_buffer,10));
            break;

        case float_lit:
            name_buffer[0] = 0;
            declaration_print2(expr->ID, "float_lit:", gcvt(expr->Float, 5,name_buffer)); //todo 5 - кол-во цифр для вывода, можно поменять
            break;

        case bool_lit:
            if(expr->Bool){
                declaration_print2(expr->ID, "bool_lit:", "true");
            }
            else{
                declaration_print2(expr->ID, "bool_lit:", "false");
            }
            break;

        case char_lit:
            name_buffer[0] = expr->Char;
            declaration_print2(expr->ID, "char_lit:", name_buffer);
            break;

        case string_lit:
            declaration_print2(expr->ID, "string_lit:", expr->String);
            break;

        case struct_expr:
            declaration_print(expr->ID, "struct_expr");
            if(expr->expr_list!=NULL){
                connection_print(expr->ID, expr->expr_list->ID);
                expr_list_print(expr->expr_list);
            }
            break;

        case struct_field_expr:
            declaration_print2(expr->ID, "identifier:",expr->Name);
            connection_print(expr->ID, expr->expr_left->ID);
            expr_print(expr->expr_left);
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

        case expr:
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
    declaration_print(stmt_list->ID, "stmt_list");

    struct stmt_node *current = stmt_list->first;
    while(current!=NULL){
        connection_print(stmt_list->ID, current->ID);
        stmt_print(current);
        current = current->next;
    }
}

void decl_stmt_print(struct decl_stmt_node *decl_stmt){
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

void let_stmt_print(struct let_stmt_node *let_stmt){

    char type[20];
    type[0] = 0;
    if(let_stmt->mutable==mut){
        strcat(type, "mutable");
    }
    else{
        strcat(type, "not_mutable");
    }
    declaration_print2(let_stmt->ID, type, let_stmt->name);

    connection_print(let_stmt->ID, let_stmt->type->ID);
    type_print(let_stmt->type);

    if(let_stmt->expr!=NULL){
        connection_print(let_stmt->ID, let_stmt->expr->ID);
        expr_print(let_stmt->expr);
    }
}

void enum_print(struct enum_node *enum_node){
    declaration_print(enum_node->ID, enum_node->name);
    if(enum_node->items!=NULL){
        connection_print(enum_node->ID, enum_node->items->ID);
        enum_list_print(enum_node->items);
    }
}

void enum_list_print(struct enum_list_node *enum_list){
    declaration_print(enum_list->ID, "enum_list");

    struct enum_item_node *current = enum_list->first;
    while(current!=NULL){
        connection_print(enum_list->ID, current->ID);
        enum_item_print(current);
        current = current->next;
    }
}

void enum_item_print(struct enum_item_node *enum_item){

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
    declaration_print2(enum_item->ID, visibility, enum_item->name);
    if(enum_item->struct_list!=NULL){
        connection_print(enum_item->ID, enum_item->struct_list->ID);
        struct_items_print(enum_item->struct_list);
    }
    if(enum_item->expr!=NULL){
        connection_print(enum_item->ID, enum_item->expr->ID);
        expr_print(enum_item->expr);
    }
}

void const_stmt_print(struct const_stmt_node *const_stmt){
    declaration_print(const_stmt->ID, const_stmt->name);
    connection_print(const_stmt->ID, const_stmt->type->ID);
    type_print(const_stmt->type);
    if(const_stmt->expr!=NULL){
        connection_print(const_stmt->ID, const_stmt->expr->ID);
        expr_print(const_stmt->expr);
    }
}

void struct_print(struct struct_node *struct_node){
    declaration_print(struct_node->ID, struct_node->name);
    if(struct_node->items!=NULL){
        connection_print(struct_node->ID, struct_node->items->ID);
        struct_items_print(struct_node->items);
    }
}

void struct_items_print(struct struct_list_node *struct_items){
    declaration_print(struct_items->ID, "struct_items_list");

    struct struct_item_node *current = struct_items->first;
    while(current!=NULL){
        connection_print(struct_items->ID, current->ID);
        struct_item_print(current);
        current = current->next;
    }
}

void struct_item_print(struct struct_item_node *struct_item){
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
    declaration_print2(struct_item->ID, visibility, struct_item->name);
    connection_print(struct_item->ID, struct_item->type->ID);
    type_print(struct_item->type);
}

void trait_print(struct trait_node *trait_node){
    declaration_print(trait_node->ID, trait_node->name);
    if(trait_node->items!=NULL){
        connection_print(trait_node->ID, trait_node->items->ID);
        associated_items_print(trait_node->items);
    }
}

void associated_items_print(struct associated_items_node *items){
    declaration_print(items->ID, "associated_items");
    if(items->first!=NULL){
        struct associated_item_node *current = items->first;
        while(current!=NULL){
            connection_print(items->ID, current->ID);
            associated_item_print(current);
            current = current->next;
        }
    }
}

void associated_item_print(struct associated_item_node *item){
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
        declaration_print2(item->ID, visibility, "function");
        connection_print(item->ID, item->fn->ID);
        function_print(item->fn);
    }
    if(item->const_stmt!=NULL){
        declaration_print2(item->ID, visibility, "const_item");
        connection_print(item->ID, item->const_stmt->ID);
        const_stmt_print(item->const_stmt);
    }
}

void impl_print(struct impl_node *impl_node){
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
        declaration_print2(impl_node->ID, impl_type, impl_node->name);
    }else{
        declaration_print(impl_node->ID, impl_type);
    }

    connection_print(impl_node->ID, impl_node->type->ID);
    type_print(impl_node->type);

    if(impl_node->items!=NULL){
        connection_print(impl_node->ID,impl_node->items->ID);
        associated_items_print(impl_node->items);
    }
}