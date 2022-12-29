package main.treeprint;
import main.nodes.*;
import main.nodes.conststmt.ConstStatementNode;
import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.enumm.EnumItemNode;
import main.nodes.enumm.EnumListNode;
import main.nodes.enumm.EnumNode;
import main.nodes.expression.ExpressionListNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.expression.ExpressionType;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionParamListNode;
import main.nodes.function.FunctionParamNode;
import main.nodes.impl.ImplNode;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;
import main.nodes.struct.StructItemNode;
import main.nodes.struct.StructListNode;
import main.nodes.struct.StructNode;
import main.nodes.trait.AssociatedItemListNode;
import main.nodes.trait.AssociatedItemNode;
import main.nodes.trait.TraitNode;
import java.io.FileWriter;
import java.io.IOException;

import static main.nodes.VarType.ARRAY;

public class Tree {

    public ProgramNode prg;
    FileWriter writer = null;
    String fileName = "tree.txt";

    public Tree(ProgramNode prg) {
        this.prg = prg;
    }

    //---------------------------------Вывод дерева в дот-------------------------------
    public void print() throws IOException {
        writer = new FileWriter(fileName, false);

        writer.write("digraph G {\n");
        declarationPrint(prg.id, "program");
        connectionPrint(prg.id, prg.stmtList.id);
        statementListPrint(prg.stmtList);
        writer.append('}');

        writer.flush();
        writer.close();
        writer = null;
    }

    private void declarationPrint(int id, String name) throws IOException {
        writer.write("id" + id + "[label=\"" + name + " id=" + id + "\"]\n");
    }

    private void declarationPrint2(int id, String type, String name) throws IOException {
        writer.write("id" + id + "[label=\"" + type + " " + name + " id=" + id + "\"]\n");
    }

    private void connectionPrint(int parentId, int childId) throws IOException {
        writer.write("id" + parentId + "->id" + childId + "\n");
    }

    private String type(VarType type) {
        return switch (type) {
            case EMPTY_TYPE -> "EMPTY_TYPE";
            case INT -> "INT";
            case CHAR -> "CHAR";
            case STRING -> "STRING";
            case FLOAT -> "FLOAT";
            case BOOL -> "BOOL";
            case ID -> "ID_TYPE";
            case ARRAY -> "ARRAY_TYPE";
        };
    }

    private void typePrint(TypeNode typeNode) throws IOException {
        if (typeNode.exprArr == null) {
            declarationPrint2(typeNode.id, "type:", type(typeNode.varType) + " " + typeNode.name);
        }
        else {
            declarationPrint2(typeNode.id, "[type; Expr]", type(typeNode.varType) + " " + typeNode.name);
        }
        if (typeNode.varType == ARRAY) {
            connectionPrint(typeNode.id, typeNode.typeArr.id);
            typePrint(typeNode.typeArr);
        }
    }

    private void functionPrint(FunctionNode fun) throws IOException {
        declarationPrint(fun.id, fun.name);
        connectionPrint(fun.id, fun.returnType.id);
        typePrint(fun.returnType);
        if (fun.paramList != null) {
            connectionPrint(fun.id, fun.paramList.id);
            functionParamsPrint(fun.paramList);
        }
        if (fun.body != null) {
            connectionPrint(fun.id, fun.body.id);
            expressionPrint(fun.body);
        }
    }

    private void functionParamsPrint(FunctionParamListNode params) throws IOException {
        String funType = switch (params.type) {
            case METHOD_SELF -> "METHOD_SELF";
            case METHOD_MUT_SELF -> "METHOD_MUT_SELF";
            case ASSOCIATED -> "ASSOCIATED";
        };
        declarationPrint2(params.id, funType, "params");
        for (FunctionParamNode element : params.list) {
            connectionPrint(params.id, element.id);
            functionParamPrint(element);
        }
    }

    private void functionParamPrint(FunctionParamNode param) throws IOException {
        declarationPrint(param.id, param.name);
        connectionPrint(param.id, param.type.id);
        typePrint(param.type);
    }

    private void expressionPrint(ExpressionNode expr) throws IOException {
        switch (expr.type) {
            case PLUS -> {
                declarationPrint(expr.id, "+");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case MINUS -> {
                declarationPrint(expr.id, "-");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case MUL -> {
                declarationPrint(expr.id, "*");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case DIV -> {
                declarationPrint(expr.id, "/");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case EQUAL -> {
                declarationPrint(expr.id, "==");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case NOT_EQUAL -> {
                declarationPrint(expr.id, "!=");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case GREATER -> {
                declarationPrint(expr.id, ">");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case LESS -> {
                declarationPrint(expr.id, "<");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case GREATER_EQUAL -> {
                declarationPrint(expr.id, ">=");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case LESS_EQUAL -> {
                declarationPrint(expr.id, "<=");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case QT -> {
                declarationPrint(expr.id, "?");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case U_MINUS -> {
                declarationPrint(expr.id, "-Expr");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case NEG -> {
                declarationPrint(expr.id, "!Expr");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case OR -> {
                declarationPrint(expr.id, "||");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case AND -> {
                declarationPrint(expr.id, "&&");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case ASGN -> {
                declarationPrint(expr.id, "'='");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case BREAK -> {
                declarationPrint(expr.id, "break");
                if (expr.exprLeft != null) {
                    connectionPrint(expr.id, expr.exprLeft.id);
                    expressionPrint(expr.exprLeft);
                }
            }
            case CONTINUE -> {
                declarationPrint(expr.id, "continue");
            }
            case RETURN -> {
                declarationPrint(expr.id, "return");
                if (expr.exprLeft != null) {
                    connectionPrint(expr.id, expr.exprLeft.id);
                    expressionPrint(expr.exprLeft);
                }
            }
            case ARRAY -> {
                declarationPrint(expr.id, "[Expr]");
                connectionPrint(expr.id, expr.exprList.id);
                expressionListPrint(expr.exprList);
            }
            case ARRAY_AUTO_FILL -> {
                declarationPrint(expr.id, "[Expr; Expr]");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case INDEX -> {
                declarationPrint(expr.id, "Expr [Expr]");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case RANGE -> {
                declarationPrint(expr.id, "..");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case RANGE_IN -> {
                declarationPrint(expr.id, "..=");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }
            case RANGE_LEFT -> {
                declarationPrint(expr.id, "Expr..");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case RANGE_RIGHT -> {
                declarationPrint(expr.id, "..Expr");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case RANGE_IN_RIGHT -> {
                declarationPrint(expr.id, "..=Expr");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case ID -> {
                declarationPrint2(expr.id, "identifier:", expr.name);
            }
            case SELF -> {
                declarationPrint2(expr.id, "this:", expr.name);
            }
            case CALL -> {
                declarationPrint2(expr.id, "method call:", expr.name);
                if (expr.exprList != null) {
                    connectionPrint(expr.id, expr.exprList.id);
                    expressionListPrint(expr.exprList);
                }
            }
            case METHOD -> {
                declarationPrint2(expr.id, "method call to Expr:", expr.name);
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                if (expr.exprList != null) {
                    connectionPrint(expr.id, expr.exprList.id);
                    expressionListPrint(expr.exprList);
                }
            }
            case FIELD_ACCESS -> {
                declarationPrint2(expr.id, "field_access:", expr.name);
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case IF -> {
                declarationPrint(expr.id, "if");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.body.id);
                expressionPrint(expr.body);
                if (expr.elseBody != null) {
                    connectionPrint(expr.id, expr.elseBody.id);
                    expressionPrint(expr.elseBody);
                }
            }
            case LOOP -> {
                declarationPrint(expr.id, "loop");
                connectionPrint(expr.id, expr.body.id);
                expressionPrint(expr.body);
            }
            case LOOP_WHILE -> {
                declarationPrint(expr.id, "while");
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                if (expr.body != null) {
                    connectionPrint(expr.id, expr.body.id);
                    expressionPrint(expr.body);
                }
            }
            case LOOP_FOR -> {
                declarationPrint(expr.id, "for " + expr.name);
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
                connectionPrint(expr.id, expr.body.id);
                expressionPrint(expr.body);
            }
            case BLOCK -> {
                declarationPrint(expr.id, "body");
                if (expr.stmtList != null) {
                    connectionPrint(expr.id, expr.stmtList.id);
                    statementListPrint(expr.stmtList);
                }
            }
            case INT_LIT -> {
                declarationPrint2(expr.id, "int_lit: ", Integer.toString(expr.anInt));
            }
            case FLOAT_LIT -> {
                declarationPrint2(expr.id, "float_lit: ", Float.toString(expr.aFloat));
            }
            case CHAR_LIT -> {
                declarationPrint2(expr.id, "char_lit: ", Character.toString(expr.aChar));
            }
            case STRING_LIT -> {
                declarationPrint2(expr.id, "string_lit: ", expr.string);
            }
            case BOOL_LIT -> {
                if (expr.aBoolean)
                    declarationPrint2(expr.id, "bool_lit: ", "true");
                else
                    declarationPrint2(expr.id, "bool_lit: ", "false");
            }
            case STRUCT -> {
                declarationPrint(expr.id, "struct_expr");
                if (expr.exprList != null) {
                    connectionPrint(expr.id, expr.exprList.id);
                    expressionListPrint(expr.exprList);
                }
            }
            case STRUCT_FIELD -> {
                declarationPrint2(expr.id, "identifier: ", expr.name);
                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);
            }
            case STATIC_METHOD -> {
                declarationPrint2(expr.id, "static method call to " + expr.parentId + ":", expr.name);
                if (expr.exprList != null) {
                    connectionPrint(expr.id, expr.exprList.id);
                    expressionListPrint(expr.exprList);
                }
            }
            case FIELD_ASGN -> {
                declarationPrint(expr.id, "Expr.Expr=");

                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);

                connectionPrint(expr.id, expr.body.id);
                expressionPrint(expr.body);

                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }

            case INDEX_ASGN -> {
                declarationPrint(expr.id, "Expr[Expr]=");

                connectionPrint(expr.id, expr.exprLeft.id);
                expressionPrint(expr.exprLeft);

                connectionPrint(expr.id, expr.body.id);
                expressionPrint(expr.body);

                connectionPrint(expr.id, expr.exprRight.id);
                expressionPrint(expr.exprRight);
            }

            case FIELD_ACCESS_NEW -> {
                declarationPrint2(expr.id, "field access:", expr.name);
            }
        }
    }

    private void expressionListPrint(ExpressionListNode exprList) throws IOException {
        declarationPrint(exprList.id, "expr_list");
        for (ExpressionNode element : exprList.list) {
            connectionPrint(exprList.id, element.id);
            expressionPrint(element);
        }
    }

    private void statementPrint(StatementNode stmt) throws IOException {
        switch (stmt.type) {
            case SEMICOLON -> {
                declarationPrint(stmt.id, ";");
            }
            case EXPRESSION -> {
                declarationPrint(stmt.id, "expr_stmt");
                connectionPrint(stmt.id, stmt.expr.id);
                expressionPrint(stmt.expr);
            }
            case DECLARATION -> {
                declarationPrint(stmt.id, "declaration_stmt");
                connectionPrint(stmt.id, stmt.declarationStmt.id);
                declarationStmtPrint(stmt.declarationStmt);
            }
            case LET -> {
                declarationPrint(stmt.id, "let_stmt");
                connectionPrint(stmt.id, stmt.letStmt.id);
                letStmtPrint(stmt.letStmt);
            }
        }
    }

    private void statementListPrint(StatementListNode stmtList) throws IOException {
        declarationPrint(stmtList.id, "stmt_list");
        for (StatementNode element : stmtList.list) {
            connectionPrint(stmtList.id, element.id);
            statementPrint(element);
        }
    }

    private void declarationStmtPrint(DeclarationStatementNode declarationStmt) throws IOException {

        switch (declarationStmt.type) {
            case ENUM -> {
                declarationPrint(declarationStmt.id,  "enum");
                connectionPrint(declarationStmt.id, declarationStmt.enumItem.id);
                enumPrint(declarationStmt.enumItem);
            }
            case FUNCTION -> {
                declarationPrint(declarationStmt.id,  "function");
                connectionPrint(declarationStmt.id, declarationStmt.functionItem.id);
                functionPrint(declarationStmt.functionItem);
            }
            case CONST_STMT -> {
                declarationPrint(declarationStmt.id,  "const_stmt");
                connectionPrint(declarationStmt.id, declarationStmt.constStmtItem.id);
                constStmtPrint(declarationStmt.constStmtItem);
            }
            case STRUCT -> {
                declarationPrint(declarationStmt.id,  "struct");
                connectionPrint(declarationStmt.id, declarationStmt.structItem.id);
                structPrint(declarationStmt.structItem);
            }
            case TRAIT -> {
                declarationPrint(declarationStmt.id,  "trait");
                connectionPrint(declarationStmt.id, declarationStmt.traitItem.id);
                traitPrint(declarationStmt.traitItem);
            }
            case IMPL -> {
                declarationPrint(declarationStmt.id,  "impl");
                connectionPrint(declarationStmt.id, declarationStmt.implItem.id);
                implPrint(declarationStmt.implItem);
            }
        }
    }

    private void letStmtPrint(LetStatementNode letStmt) throws IOException {
        String type;
        if (letStmt.mut == Mutable.MUT) {
            type = "mutable";
        }
        else {
            type = "not_mutable";
        }
        declarationPrint2(letStmt.id, type, letStmt.name);
        connectionPrint(letStmt.id, letStmt.type.id);
        typePrint(letStmt.type);
        if (letStmt.expr != null) {
            connectionPrint(letStmt.id, letStmt.expr.id);
            expressionPrint(letStmt.expr);
        }
    }

    private void enumPrint(EnumNode enumNode) throws IOException {
        declarationPrint(enumNode.id, "enum_list");
        if (enumNode.enumList != null) {
            connectionPrint(enumNode.id, enumNode.enumList.id);
            enumListPrint(enumNode.enumList);
        }
    }

    private void enumListPrint(EnumListNode enumList) throws IOException {
        declarationPrint(enumList.id, "enum_list");
        for (EnumItemNode element : enumList.list) {
            connectionPrint(enumList.id, element.id);
            enumItemPrint(element);
        }
    }

    private void enumItemPrint(EnumItemNode enumItem) throws IOException {

        declarationPrint(enumItem.id, enumItem.name);
        if (enumItem.structList != null) {
            connectionPrint(enumItem.id, enumItem.structList.id);
            structItemListPrint(enumItem.structList);
        }
        if (enumItem.expr != null) {
            connectionPrint(enumItem.id, enumItem.expr.id);
            expressionPrint(enumItem.expr);
        }
    }

    private void constStmtPrint(ConstStatementNode constStmt) throws IOException {
        declarationPrint(constStmt.id, constStmt.name);
        connectionPrint(constStmt.id, constStmt.type.id);
        typePrint(constStmt.type);
        if (constStmt.expr != null) {
            connectionPrint(constStmt.id, constStmt.expr.id);
            expressionPrint(constStmt.expr);
        }
    }

    private void structPrint(StructNode struct) throws IOException {
        declarationPrint(struct.id, struct.name);
        if (struct.structList != null) {
            connectionPrint(struct.id, struct.structList.id);
            structItemListPrint(struct.structList);
        }
    }

    private void structItemListPrint(StructListNode structList) throws IOException {
        declarationPrint(structList.id, "struct_items_list");
        for (StructItemNode element : structList.list) {
            connectionPrint(structList.id, element.id);
            structItemPrint(element);
        }
    }

    private void structItemPrint(StructItemNode structItem) throws IOException {

        declarationPrint(structItem.id, structItem.name);
        connectionPrint(structItem.id, structItem.type.id);
        typePrint(structItem.type);
    }

    private void traitPrint(TraitNode trait) throws IOException {
        declarationPrint(trait.id, trait.name);
        if (trait.associatedItemList != null) {
            connectionPrint(trait.id, trait.associatedItemList.id);
            associatedItemListPrint(trait.associatedItemList);
        }
    }

    private void associatedItemListPrint(AssociatedItemListNode items) throws IOException {
        declarationPrint(items.id, "associated_items");
        if (items.list != null) {
            for (AssociatedItemNode element : items.list) {
                connectionPrint(items.id, element.id);
                associatedItemPrint(element);
            }
        }
    }

    private void associatedItemPrint(AssociatedItemNode item) throws IOException {

        if (item.fun != null) {
            declarationPrint(item.id,  "function");
            connectionPrint(item.id, item.fun.id);
            functionPrint(item.fun);
        }
        if (item.constStmt != null) {
            declarationPrint(item.id,  "const_item");
            connectionPrint(item.id, item.constStmt.id);
            constStmtPrint(item.constStmt);
        }
    }

    private void implPrint(ImplNode impl) throws IOException {
        String implType = impl.implType.toString();

        if (impl.name != null)
            declarationPrint2(impl.id, implType, impl.name);
        else
            declarationPrint(impl.id, implType);

        connectionPrint(impl.id, impl.typeNode.id);
        typePrint(impl.typeNode);

        if (impl.associatedItemList != null) {
            connectionPrint(impl.id, impl.associatedItemList.id);
            associatedItemListPrint(impl.associatedItemList);
        }
    }

    //------------------------------Преобразование дерева-----------------------------------//
    public void transform(){
        this.prg.stmtList.list.forEach(this::stmtTransform);
    }

    private void exprTransform(ExpressionNode expr){
        //Преобразование присваивания
        if (expr.type == ExpressionType.ASGN) {
            switch (expr.exprLeft.type) {
                case INDEX -> {
                    expr.type = ExpressionType.INDEX_ASGN;
                    expr.body = expr.exprLeft.exprRight;
                    expr.exprLeft = expr.exprLeft.exprLeft;
                }
                case FIELD_ACCESS -> {
                    expr.type = ExpressionType.FIELD_ASGN;
                    expr.body = expr.exprLeft;
                    expr.exprLeft = expr.exprLeft.exprLeft;
                    expr.body.exprLeft = null;
                    expr.body.type = ExpressionType.FIELD_ACCESS_NEW;
                }
            }
        }else if(expr.type == ExpressionType.BLOCK){
            expr.stmtList.list.forEach(this::stmtTransform);
        }
    }

    private void stmtTransform(StatementNode stmt){
        switch (stmt.type) {
            case EXPRESSION -> {
                exprTransform(stmt.expr);
            }
            case DECLARATION -> {
                declarationTransform(stmt.declarationStmt);
            }
            case LET -> {
                exprTransform(stmt.letStmt.expr);
            }
        }
    }

    private void declarationTransform(DeclarationStatementNode decl){
        switch (decl.type){
            case FUNCTION -> functionTransform(decl.functionItem);
            case CONST_STMT -> constStmtTransform(decl.constStmtItem);
            case TRAIT -> traitTransform(decl.traitItem);
            case IMPL -> implTransform(decl.implItem);
        }
    }

    private void exprListTransform(ExpressionListNode exprList){
        exprList.list.forEach(this::exprTransform);
    }

    private void constStmtTransform(ConstStatementNode constStmt){
        if(constStmt.expr!=null){
            exprTransform(constStmt.expr);
        }
    }

    private void functionTransform(FunctionNode func){
        if(func.body!=null){
            exprTransform(func.body);
        }
    }

    private void traitTransform(TraitNode trait){
        if(trait.associatedItemList.list.size()>0){
            trait.associatedItemList.list.forEach(this::associatedItemTransform);
        }
    }

    private void implTransform(ImplNode impl){
        if(impl.associatedItemList.list.size()>0){
            impl.associatedItemList.list.forEach(this::associatedItemTransform);
        }
    }

    private void associatedItemTransform(AssociatedItemNode item){
        if(item.fun!=null){
            functionTransform(item.fun);
        }
        if(item.constStmt!=null){
            constStmtTransform(item.constStmt);
        }
    }
}
