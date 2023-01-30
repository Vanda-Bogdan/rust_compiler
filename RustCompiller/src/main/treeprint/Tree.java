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
import main.semantic.ClassTable;
import main.semantic.FieldTable;
import main.semantic.Tables;

import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Map;
import java.util.Objects;
import java.util.Vector;

import static main.nodes.VarType.*;

public class Tree {

    public ProgramNode prg;
    FileWriter writer = null;
    String fileName = "tree.txt";

    public Tree(ProgramNode prg) {
        this.prg = prg;
    }

    //-----------------------Таблицы--------------------------
    public Tables tables;

    public void createTables() {
        tables = new Tables();
        tables.createTables(this);
        tables.outputTablesToFiles();
    }

    //----- счетчик для проверки break в циклах ------
    int insideLoop = 0;

    public ExpressionType currentLoopType = ExpressionType.QT;

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
            case VOID -> "VOID";
            case UNDEFINED -> "UNDEFINED";
            case INT -> "INT";
            case CHAR -> "CHAR";
            case STRING -> "STRING";
            case FLOAT -> "FLOAT";
            case BOOL -> "BOOL";
            case ID -> "ID_TYPE";
            case ARRAY -> "ARRAY";
        };
    }

    private void typePrint(TypeNode typeNode) throws IOException {
        if (typeNode.exprArr == null) {
            declarationPrint2(typeNode.id, "type:", type(typeNode.varType) + " " + typeNode.name);
        } else {
            declarationPrint2(typeNode.id, "[type; Expr]", type(typeNode.varType) + " " + typeNode.name);
        }
        if (typeNode.varType == ARRAY) {
            connectionPrint(typeNode.id, typeNode.typeArr.id);
            connectionPrint(typeNode.id, typeNode.exprArr.id);
            expressionPrint(typeNode.exprArr);
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
                declarationPrint2(expr.id, "Expr.", expr.name);
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
                declarationPrint2(expr.id, "struct_expr:", expr.name);
                if (expr.exprList != null) {
                    connectionPrint(expr.id, expr.exprList.id);
                    expressionListPrint(expr.exprList);
                }
            }
            case STRUCT_FIELD -> {
                declarationPrint2(expr.id, "struct_field: ", expr.name);
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
                declarationPrint2(expr.id, "field access new:", expr.name);
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
                declarationPrint(declarationStmt.id, "enum");
                connectionPrint(declarationStmt.id, declarationStmt.enumItem.id);
                enumPrint(declarationStmt.enumItem);
            }
            case FUNCTION -> {
                declarationPrint(declarationStmt.id, "function");
                connectionPrint(declarationStmt.id, declarationStmt.functionItem.id);
                functionPrint(declarationStmt.functionItem);
            }
            case CONST_STMT -> {
                declarationPrint(declarationStmt.id, "const_stmt");
                connectionPrint(declarationStmt.id, declarationStmt.constStmtItem.id);
                constStmtPrint(declarationStmt.constStmtItem);
            }
            case STRUCT -> {
                declarationPrint(declarationStmt.id, "struct");
                connectionPrint(declarationStmt.id, declarationStmt.structItem.id);
                structPrint(declarationStmt.structItem);
            }
            case TRAIT -> {
                declarationPrint(declarationStmt.id, "trait");
                connectionPrint(declarationStmt.id, declarationStmt.traitItem.id);
                traitPrint(declarationStmt.traitItem);
            }
            case IMPL -> {
                declarationPrint(declarationStmt.id, "impl");
                connectionPrint(declarationStmt.id, declarationStmt.implItem.id);
                implPrint(declarationStmt.implItem);
            }
        }
    }

    private void letStmtPrint(LetStatementNode letStmt) throws IOException {
        String type;
        if (letStmt.mut == Mutable.MUT) {
            type = "mutable";
        } else {
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
            declarationPrint(item.id, "function");
            connectionPrint(item.id, item.fun.id);
            functionPrint(item.fun);
        }
        if (item.constStmt != null) {
            declarationPrint(item.id, "const_item");
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
    public void transform() {
        this.prg.stmtList.list.forEach(this::stmtTransform);
    }

    private void exprTransform(ExpressionNode expr) {
        if (expr == null) {
            return;
        }
        switch (expr.type) {
            case PLUS:
            case MINUS:
            case DIV:
            case MUL:
            case EQUAL:
            case NOT_EQUAL:
            case GREATER:
            case LESS:
            case GREATER_EQUAL:
            case LESS_EQUAL:
            case OR:
            case AND:
            case RANGE:
            case RANGE_IN:
            case INDEX:
            case ARRAY_AUTO_FILL:
                exprTransform(expr.exprLeft);
                exprTransform(expr.exprRight);
                break;
            case RANGE_LEFT:
            case RANGE_RIGHT:
            case RANGE_IN_RIGHT:
            case QT:
            case U_MINUS:
            case NEG:
            case STRUCT_FIELD:
            case FIELD_ACCESS:
                exprTransform(expr.exprLeft);
                break;
            case BREAK:
            case RETURN:
                if (expr.exprLeft != null) {
                    exprTransform(expr.exprLeft);
                }
                break;
            case ARRAY:
                exprListTransform(expr.exprList);
                break;
            case CALL:
            case STATIC_METHOD:
            case STRUCT:
                if (expr.exprList != null) {
                    exprListTransform(expr.exprList);
                }
                break;
            case METHOD:
                exprTransform(expr.exprLeft);
                if (expr.exprList != null) {
                    exprListTransform(expr.exprList);
                }
                break;
            case IF:
                exprTransform(expr.exprLeft);
                exprTransform(expr.body);
                if (expr.elseBody != null) {
                    exprTransform(expr.elseBody);
                }
                break;
            case LOOP:
                exprTransform(expr.body);
                break;
            case LOOP_FOR:
                exprTransform(expr.exprLeft);
                exprTransform(expr.body);
                break;
            case LOOP_WHILE:
                exprTransform(expr.exprLeft);
                if (expr.body != null) {
                    exprTransform(expr.body);
                }
                break;
            case BLOCK:
                if(expr.stmtList!=null){
                    expr.stmtList.list.forEach(this::stmtTransform);
                }
                break;
            case ASGN:
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
                break;
        }
    }

    private void stmtTransform(StatementNode stmt) {
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

    private void declarationTransform(DeclarationStatementNode decl) {
        switch (decl.type) {
            case FUNCTION -> functionTransform(decl.functionItem);
            case CONST_STMT -> constStmtTransform(decl.constStmtItem);
            case TRAIT -> traitTransform(decl.traitItem);
            case IMPL -> implTransform(decl.implItem);
        }
    }

    private void exprListTransform(ExpressionListNode exprList) {
        exprList.list.forEach(this::exprTransform);
    }

    private void constStmtTransform(ConstStatementNode constStmt) {
        if (constStmt.expr != null) {
            exprTransform(constStmt.expr);
        }
    }

    private void functionTransform(FunctionNode func) {
        if (func.body != null) {
            exprTransform(func.body);
        }
    }

    private void traitTransform(TraitNode trait) {
        if (trait.associatedItemList != null && trait.associatedItemList.list.size() > 0) {
            trait.associatedItemList.list.forEach(this::associatedItemTransform);
        }
    }

    private void implTransform(ImplNode impl) {
        if (impl.associatedItemList != null && impl.associatedItemList.list.size() > 0) {
            impl.associatedItemList.list.forEach(this::associatedItemTransform);
        }
    }

    private void associatedItemTransform(AssociatedItemNode item) {
        if (item.fun != null) {
            functionTransform(item.fun);
        }
        if (item.constStmt != null) {
            constStmtTransform(item.constStmt);
        }
    }

    //----------------------------------- Проверка соответствия типов-------------------------------------
    public void typesCheck() {
        this.prg.stmtList.list.forEach(this::stmtTypes);
    }

    private void stmtTypes(StatementNode stmt) {
        switch (stmt.type) {
            case EXPRESSION -> exprTypes(stmt.expr);
            case DECLARATION -> declarationTypes(stmt.declarationStmt);
            case LET -> letTypes(stmt.letStmt);
        }
    }

    private void letTypes(LetStatementNode let) {
        if (let.expr != null) {
            exprTypes(let.expr);
            if(let.expr.countedType.varType==UNDEFINED){
                throw new IllegalArgumentException("При инициализации " + let.name + " используется выражение неопределенного типа (ID: " + let.expr.id + ")");
            }
            if (let.type.varType == UNDEFINED || let.type.equals(let.expr.countedType)) {
                let.setVarType(let.expr.countedType);
            } else {
                throw new IllegalArgumentException("Несоответствие типов в объявлении " + let.name + "(ID: " + let.id + "). Ожидался тип " + let.type.getName() + ", реальный - " + let.expr.countedType.getName());
            }
        }
    }

    private void exprTypes(ExpressionNode expr) {
        switch (expr.type) {
            case CALL -> {
                //проверка совпадений типов переданных параметров функции
                if (expr.methodTableItem() == null) {
                    throw new IllegalArgumentException("Неизвестная функция " + expr.name + "(ID: " + expr.id + ")");
                } else {
                    ArrayList<FunctionParamNode> paramList = expr.methodTableItem().params().list;
                    if (expr.exprList == null) {
                        if (paramList.size() > 0) {
                            throw new IllegalArgumentException("Несоответствие кол-ва параметров функции " + expr.name + ". Требуется " + paramList.size() + " параметров. (ID: " + expr.id + ")");
                        }
                        expr.defineTypeOfExpr();
                    }
                    else if (expr.exprList.list.size() != paramList.size()) {
                        throw new IllegalArgumentException("Несоответствие кол-ва параметров функции " + expr.name + ". Требуется " + paramList.size() + " параметров. (ID: " + expr.id + ")");
                    }
                    else {
                        int num = 0;
                        for (ExpressionNode param : expr.exprList.list) {
                            exprTypes(param);
                            if (num > paramList.size() - 1) {
                                throw new IllegalArgumentException("Лишний параметр (ID: " + param.id + ") вызова функции " + expr.name + "(ID: " + expr.id + ")");
                            } else if (!paramList.get(num).type.equals(param.countedType)) {
                                throw new IllegalArgumentException("Несоответствие типа " + (num + 1) + "-го по счету параметра (name: " + paramList.get(num).name + ", ID: " + param.id + ") вызова функции " + expr.name + "(ID: " + expr.id + "). Ожидаемый тип: " + paramList.get(num).type.getName() + ", реальный: " + param.countedType.getName());
                            }
                            num++;
                        }
                    }
                    expr.defineTypeOfExpr();
                }

            }

            case METHOD -> {
                exprTypes(expr.exprLeft);
                ClassTable classTable = tables.tableByName(expr.exprLeft.countedType.name);
                if (classTable == null) {
                    throw new IllegalArgumentException("Вызов метода к неизвестному классу " + expr.exprLeft.countedType.name + "(ID: " + expr.id + ")");
                }
                expr.setMethod(expr.name, classTable.methods());
                if (expr.methodTableItem() == null) {
                    throw new IllegalArgumentException("Неизвестный метод " + expr.name + " для класса " + expr.exprLeft.countedType.name + "(ID: " + expr.id + ")");
                }

                ArrayList<FunctionParamNode> paramList = expr.methodTableItem().params().list;

                if (expr.exprList == null) {
                    if (paramList.size() > 0) {
                        throw new IllegalArgumentException("Несоответствие кол-ва параметров метода " + expr.name + ". Требуется " + paramList.size() + " параметров. (ID: " + expr.id + ")");
                    }
                    expr.defineTypeOfExpr();
                }
                else if (expr.exprList.list.size() != paramList.size()) {
                    throw new IllegalArgumentException("Несоответствие кол-ва параметров метода " + expr.name + ". Требуется " + paramList.size() + " параметров. (ID: " + expr.id + ")");
                }
                else {
                    int num = 0;
                    for (ExpressionNode param : expr.exprList.list) {
                        param.defineTypeOfExpr();
                        if (num > paramList.size() - 1) {
                            throw new IllegalArgumentException("Лишний параметр (ID: " + param.id + ") вызова метода " + expr.name + "(ID: " + expr.id + ")");
                        } else if (!paramList.get(num).type.equals(param.countedType)) {
                            throw new IllegalArgumentException("Несоответствие типа " + (num + 1) + "-го по счету параметра (name: " + paramList.get(num).name + ", ID: " + param.id + ") вызова функции " + expr.name + "(ID: " + expr.id + "). Ожидаемый тип: " + paramList.get(num).type.getName() + ", реальный: " + param.countedType.getName());
                        }
                        num++;
                    }
                    expr.defineTypeOfExpr();
                }
            }

            case STATIC_METHOD -> {
                ClassTable classTable = tables.tableByName(expr.parentId);
                if (classTable == null) {
                    throw new IllegalArgumentException("Неизвестный класс " + expr.parentId + "(ID: " + expr.id + ")");
                }
                expr.setMethod(expr.name, classTable.methods());
                if (expr.methodTableItem() == null) {
                    throw new IllegalArgumentException("Неизвестный статический метод " + expr.name + " для класса " + expr.parentId + "(ID: " + expr.id + ")");
                }

                ArrayList<FunctionParamNode> paramList = expr.methodTableItem().params().list;

                if (expr.exprList == null) {
                    if (paramList.size() > 0) {
                        throw new IllegalArgumentException("Несоответствие кол-ва параметров статического метода " + expr.name + ". Требуется " + paramList.size() + " параметров. (ID: " + expr.id + ")");
                    }
                    expr.defineTypeOfExpr();
                }
                else if (expr.exprList.list.size() != paramList.size()) {
                    throw new IllegalArgumentException("Несоответствие кол-ва параметров статического метода " + expr.name + ". Требуется " + paramList.size() + " параметров. (ID: " + expr.id + ")");
                }
                else {
                    int num = 0;
                    for (ExpressionNode param : expr.exprList.list) {
                        param.defineTypeOfExpr();
                        if (num > paramList.size() - 1) {
                            throw new IllegalArgumentException("Лишний параметр (ID: " + param.id + ") вызова метода " + expr.name + "(ID: " + expr.id + ")");
                        } else if (!paramList.get(num).type.equals(param.countedType)) {
                            throw new IllegalArgumentException("Несоответствие типа параметра " + param.name + "(ID: " + param.id + ") вызова функции " + expr.name + "(ID: " + expr.id + "). Ожидаемый тип: " + paramList.get(num).type.getName() + ", реальный: " + param.countedType.getName());
                        }
                        num++;
                    }
                    expr.defineTypeOfExpr();
                }

            }

            case STRUCT -> {
                ClassTable struct = tables.tableByName(expr.name);
                if (struct == null) {
                    throw new IllegalArgumentException("Объявление неизвестной структуры " + expr.name + "(ID: " + expr.id + ")");
                }
                FieldTable structFields = struct.fields();

                if (expr.exprList == null) {
                    if (structFields.items.size() > 0) {
                        throw new IllegalArgumentException("Несоответствие кол-ва полей при инициализации объекта структуры " + expr.name + ". ID: " + expr.id);
                    }
                }
                else if (expr.exprList.list.size() != structFields.amountNotConst()) {
                    throw new IllegalArgumentException("Несоответствие кол-ва полей при инициализации объекта структуры " + expr.name + ". Требуется " + structFields.items.size() + " полей, получено " + expr.exprList.list.size() + " полей. (ID: "+ expr.id + ")");
                }
                else {
                    for (ExpressionNode param : expr.exprList.list) {
                        if (param.type != ExpressionType.STRUCT_FIELD) {
                            throw new IllegalArgumentException("Неверное выражение (ID: " + param.id + ") типа " + param.type.toString() + " при инициализации объекта структуры " + expr.name);
                        } else if (!structFields.contains(param.name)) {
                            throw new IllegalArgumentException("Неизвестный параметр " + param.name + "(ID: " + param.id + ") при инициализации объекта структуры " + expr.name);
                        }
                        param.exprLeft.defineTypeOfExpr();
                        TypeNode expectedType = structFields.get(param.name).type();
                        if (!expectedType.equals(param.exprLeft.countedType)) {
                            throw new IllegalArgumentException("Для параметра " + param.name + "(ID: " + param.id + ") при инициализации объекта структуры " + expr.name + " ожидался тип: " + expectedType.getName() + ", реальный тип - " + param.exprLeft.countedType.getName());
                        }
                    }
                    expr.defineTypeOfExpr();
                }
            }
            case IF -> {
                exprTypes(expr.exprLeft);
                if (expr.exprLeft.countedType.varType != VarType.BOOL) {
                    throw new IllegalArgumentException("В условии if ожидается bool выражение (ID:" + expr.id + ")");
                }
                exprTypes(expr.body);
                if(expr.elseBody!=null){
                    exprTypes(expr.elseBody);
                    if(expr.body.countedType.varType!=UNDEFINED && expr.body.countedType.equals(expr.elseBody.countedType)){
                        expr.countedType = expr.body.countedType;
                    }
                    else {
                        expr.countedType = new TypeNode(UNDEFINED);
                    }
                }

                expr.defineTypeOfExpr();
            }

            case FIELD_ACCESS -> {
                exprTypes(expr.exprLeft);
                if(expr.exprLeft.countedType.varType!=VarType.ID){
                    throw new IllegalArgumentException("Доступ к полю возможен только у идентификатора (ID: " + expr.exprLeft.id + ")");
                }
                ClassTable classTable = tables.tableByName(expr.exprLeft.countedType.name);
                if (classTable == null) {
                    throw new IllegalArgumentException("Неизвестный класс " + expr.exprLeft.countedType.name + "(ID: " + expr.exprLeft.id + ")");
                }
                if(!classTable.containsField(expr.name)){
                    throw new IllegalArgumentException("Доступ к неизвестному полю " + expr.name + " класса " + classTable.name + " (ID: " + expr.id + ")");
                }
                expr.setField(expr.name, classTable.fields());
                expr.countedType = expr.fieldTableItem().type();
                expr.setTypeFromField();
            }

            case FIELD_ASGN -> {
                exprTypes(expr.exprLeft);
                if(expr.exprLeft.countedType.varType!=VarType.ID){
                    throw new IllegalArgumentException("Доступ к полю возможен только у идентификатора (ID: " + expr.exprLeft.id + ")");
                }
                if(expr.exprLeft.variableTableItem().isMut()==Mutable.NOT_MUT){
                    throw new IllegalArgumentException("Нельзя переопределить поле " + expr.body.name + " у неизменяемого " + expr.exprLeft.name + " (ID: " + expr.id + ")");
                }

                ClassTable classTable = tables.tableByName(expr.exprLeft.countedType.name);
                if (classTable == null) {
                    throw new IllegalArgumentException("Неизвестный класс " + expr.exprLeft.countedType.name + " (ID: " + expr.exprLeft.id + ")");
                }
                if(!classTable.containsField(expr.body.name)){
                    throw new IllegalArgumentException("Доступ к неизвестному полю " + expr.body.name + " класса " + classTable.name + " (ID: " + expr.body.id + ")");
                }

                expr.body.setField(expr.body.name, classTable.fields());
                expr.body.setTypeFromField();
                exprTypes(expr.exprRight);

                if(!expr.body.countedType.equals(expr.exprRight.countedType)){
                    throw new IllegalArgumentException("Нельзя присвоить полю " + expr.body.name + " типа " + expr.body.countedType.getName() + " выражение типа " + expr.exprRight.countedType.getName() + " (ID: " + expr.id + ")");
                }
            }

            case ASGN -> {
                if(expr.exprLeft.type!=ExpressionType.ID){
                    throw new IllegalArgumentException("Невозможно присвоение выражению типа " + expr.exprLeft.type.toString() + "(ID: " + expr.exprLeft.id + ")");
                }
                checkMutabilityAsgn(expr.exprLeft);
                exprTypes(expr.exprLeft);
                exprTypes(expr.exprRight);
                checkInitialization(expr.exprRight);
                if(!expr.exprLeft.countedType.equals(expr.exprRight.countedType)){
                    throw new IllegalArgumentException("Ошибка присвоения (ID: " + expr.id + "). Ожидался тип " + expr.exprLeft.countedType.getName() + ", реальный - " + expr.exprRight.countedType.getName());
                }
                expr.exprLeft.countedType = expr.exprRight.countedType;
                expr.exprLeft.setInitializated();
                expr.defineTypeOfExpr();
            }

            //---------------------------- Арифметические и логические -----------------------------
            case PLUS, MINUS, MUL, DIV -> {
                exprTypes(expr.exprLeft);
                exprTypes(expr.exprRight);

                checkInitialization(expr.exprLeft);
                checkInitialization(expr.exprRight);

                if (expr.exprLeft.countedType.varType == VarType.INT && expr.exprRight.countedType.varType == VarType.INT) {
                    expr.countedType = new TypeNode(VarType.INT);
                }
                else if (expr.exprLeft.countedType.varType == VarType.FLOAT && expr.exprRight.countedType.varType == VarType.FLOAT) {
                    expr.countedType = new TypeNode(VarType.FLOAT);
                }
                else {
                    throw new IllegalArgumentException("Неверные типы выражений при выполнении арифметической операции (ID: " + expr.id + "). Типы " + expr.exprLeft.countedType.getName() + " и " + expr.exprRight.countedType.getName() + " несовместимы");
                }

                expr.defineTypeOfExpr();
            }
            case EQUAL, NOT_EQUAL, GREATER, LESS, GREATER_EQUAL, LESS_EQUAL -> {
                exprTypes(expr.exprLeft);
                exprTypes(expr.exprRight);
                checkInitialization(expr.exprLeft);
                checkInitialization(expr.exprRight);
                TypeNode leftType = expr.exprLeft.countedType;
                if (leftType.equals(expr.exprRight.countedType)) {
                    if(leftType.varType != INT && leftType.varType!= FLOAT && leftType.varType != BOOL && leftType.varType != STRING && leftType.varType != CHAR){//todo не все можно сравнить, например классы
                        throw new IllegalArgumentException("Тип " + leftType.getName() + " не поддается сравнению (ID: " + expr.id + ")");
                    }
                    expr.defineTypeOfExpr();
                }
                else {
                    throw new IllegalArgumentException("Несовместимые типы для выполнения операции сравнения (ID: " + expr.id + ")");
                }
            }
            case U_MINUS -> {
                exprTypes(expr.exprLeft);
                checkInitialization(expr.exprLeft);
                if (expr.exprLeft.countedType.varType == VarType.INT) {
                    expr.countedType = new TypeNode(VarType.INT);
                }
                else if (expr.exprLeft.countedType.varType == VarType.FLOAT) {
                    expr.countedType = new TypeNode(VarType.FLOAT);
                }
                else {
                    throw new IllegalArgumentException("Невозможно применить унарный минус к выражению типа " + expr.exprLeft.countedType.getName() + " (ID:" + expr.id + ")");
                }
            }
            case NEG -> {
                exprTypes(expr.exprLeft);
                checkInitialization(expr.exprLeft);

                if (expr.exprLeft.countedType.varType == VarType.BOOL) {
                    expr.defineTypeOfExpr();
                }
                else {
                    throw new IllegalArgumentException("Невозможно применить отрицание к выражению типа" + expr.exprLeft.countedType.getName() + " (ID:" + expr.id + ")");
                }
            }
            case OR, AND -> {
                exprTypes(expr.exprLeft);
                exprTypes(expr.exprRight);
                checkInitialization(expr.exprLeft);
                checkInitialization(expr.exprRight);
                if (expr.exprLeft.countedType.varType == VarType.BOOL && expr.exprRight.countedType.varType == VarType.BOOL) {
                    expr.defineTypeOfExpr();
                }
                else {
                    throw new IllegalArgumentException("Невозможно применить логические И / ИЛИ к не boolean выражениям (ID:" + expr.id + "). Предоставленные типы: " + expr.exprLeft.countedType.getName() + " " + expr.exprRight.countedType.getName());
                }
            }
            //------------------------- LOOP --------------------------------
            case LOOP_WHILE -> {
                currentLoopType = ExpressionType.LOOP_WHILE;
                insideLoop++;
                exprTypes(expr.exprLeft);
                checkInitialization(expr.exprLeft);

                if(expr.exprLeft.countedType.varType!=BOOL){
                    throw new IllegalArgumentException("Выражение в условии while(ID: " + expr.id + ") должно возвращать bool");
                }
                expr.defineTypeOfExpr();
                exprTypes(expr.body);
                insideLoop--;
                currentLoopType = ExpressionType.QT;
            }
            case LOOP_FOR -> {
                currentLoopType = ExpressionType.LOOP_FOR;
                insideLoop++;
                ExpressionType type = expr.exprLeft.type;
                if(type!= ExpressionType.RANGE && type!=ExpressionType.RANGE_IN && type!=ExpressionType.RANGE_RIGHT
                        && type!=ExpressionType.RANGE_IN_RIGHT && type!=ExpressionType.RANGE_LEFT && type!=ExpressionType.ID){
                    throw new IllegalArgumentException("Неверное RANGE выражение в цикле for (ID: " + expr.id + ")");
                }
                expr.defineTypeOfExpr();
                exprTypes(expr.exprLeft);
                exprTypes(expr.body);
                insideLoop--;
                currentLoopType = ExpressionType.QT;
            }
            case LOOP -> {
                currentLoopType = ExpressionType.LOOP;
                insideLoop++;
                // Массив break
                ArrayList<ExpressionNode> breaks = new ArrayList<>();

                // Получение возвращаемого типа break и проверка идентичности типов во всех break
                expr.body.findBreakInBlock(breaks);
                for (int i = 0; i < breaks.size(); i++) {
                    exprTypes(breaks.get(i));
                    if (i > 0 && !Objects.equals(breaks.get(0).countedType.getName(), breaks.get(i).countedType.getName())) {
                        throw new IllegalArgumentException("В break ожидается тип " + breaks.get(0).countedType.getName()
                                + ", получен " + breaks.get(i).countedType.getName() + "(ID: " + breaks.get(i).id + ")");
                    }
                }
                if (breaks.size() == 0)
                    expr.countedType =  new TypeNode(VarType.VOID);
                else
                    expr.countedType = breaks.get(0).countedType;

                exprTypes(expr.body);
                insideLoop--;
                currentLoopType = ExpressionType.QT;
            }
            //------------------------- ARRAY --------------------------------
            case ARRAY -> {
                ExpressionListNode exprList = expr.exprList;
                TypeNode currentType = new TypeNode(ARRAY);
                if(exprList==null){
                    currentType.typeArr = new TypeNode(UNDEFINED);
                    expr.countedType = currentType;
                }
                else {
                    TypeNode bufferType;
                    if(exprList.list.size()>0){
                        exprTypes(exprList.list.get(0));
                        checkInitialization(exprList.list.get(0));
                        currentType.typeArr = exprList.list.get(0).countedType;
                        for (ExpressionNode curExpr: exprList.list) {
                            exprTypes(curExpr);
                            bufferType = curExpr.countedType;
                            if(!bufferType.equals(currentType.typeArr)){
                                throw new IllegalArgumentException("Неверный тип узла " + curExpr.id + ": " + curExpr.countedType.getName() + " для массива с элементами типа " + currentType.typeArr.getName());
                            }
                        }
                    }
                    currentType.exprArr = new ExpressionNode(exprList.list.size());
                    expr.countedType = currentType;
                }
            }
            case INDEX -> {
                exprTypes(expr.exprLeft);
                exprTypes(expr.exprRight);
                checkInitialization(expr.exprLeft);
                checkInitialization(expr.exprRight);

                if (expr.exprLeft.countedType.varType != VarType.ARRAY) {
                    throw new IllegalArgumentException("У данного типа нет операции обращения по индексу (ID:" + expr.id + ")");
                }
                if (expr.exprRight.countedType.varType!=INT){
                    throw new IllegalArgumentException("Номер взятия по индексу должен быть INT (ID: " + expr.exprRight.id + ")");
                }

                expr.defineTypeOfExpr();
            }
            case INDEX_ASGN -> {
                if(expr.exprLeft.variableTableItem()!=null && expr.exprLeft.variableTableItem().isMut()==Mutable.NOT_MUT) {
                    throw new IllegalArgumentException("Невозможно присвоение элементу неизменяемого массива " + expr.exprLeft.name + " (ID: " + expr.exprLeft.id + ")");
                }
                exprTypes(expr.body);
                checkMutabilityAsgn(expr.exprLeft);
                if(expr.body.countedType.varType!=INT){
                    throw new IllegalArgumentException("Номер взятия по индексу должен быть INT (ID: " + expr.body.id + ")");
                }
                exprTypes(expr.exprRight);
                exprTypes(expr.exprLeft);
                checkInitialization(expr.exprLeft);
                checkInitialization(expr.exprRight);

                if(!expr.exprLeft.countedType.typeArr.equals(expr.exprRight.countedType)){
                    throw new IllegalArgumentException("Неверное присвоение элементу массива " + expr.exprLeft.name + ". Ожидался тип " + expr.exprLeft.countedType.typeArr.getName() + ", реальный: " + expr.exprRight.countedType.getName() + ". (ID: " + expr.id + ")");
                }
            }
            //------------------------- RANGE --------------------------------
            case RANGE, RANGE_IN, RANGE_LEFT, RANGE_RIGHT, RANGE_IN_RIGHT -> {
                if (expr.exprLeft != null) {
                    exprTypes(expr.exprLeft);
                    if (expr.exprLeft.countedType.varType != VarType.INT) {
                        throw new IllegalArgumentException("Не int тип для левого выражения range (ID:" + expr.id + ")");
                    }
                    checkInitialization(expr.exprLeft);
                }
                if (expr.exprRight != null) {
                    exprTypes(expr.exprRight);
                    if (expr.exprRight.countedType.varType != VarType.INT) {
                        throw new IllegalArgumentException("Не int тип для правого выражения range (ID:" + expr.id + ")");
                    }
                    checkInitialization(expr.exprRight);
                }
            }

            //------------------------- Остальное ----------------------------------
            case RETURN, STRUCT_FIELD -> {
                if(expr.exprLeft!=null){
                    exprTypes(expr.exprLeft);
                    expr.defineTypeOfExpr();
                    checkInitialization(expr.exprLeft);
                }
                else {
                    expr.countedType = new TypeNode(VOID);
                }
            }
            case BREAK -> {
                if(insideLoop == 0){
                    throw new IllegalArgumentException("Непредвиденный break вне цикла (ID: " + expr.id + ")");
                }
                if(expr.exprLeft!=null){
                    if(currentLoopType==ExpressionType.LOOP_FOR || currentLoopType==ExpressionType.LOOP_WHILE){
                        throw new IllegalArgumentException("break с выражением возможен только в цикле loop (ID: " + expr.id + ")");
                    }
                    exprTypes(expr.exprLeft);
                    expr.defineTypeOfExpr();
                    checkInitialization(expr.exprLeft);
                }
                else {
                    expr.countedType = new TypeNode(VOID);
                }
            }

            case ARRAY_AUTO_FILL -> {
                exprTypes(expr.exprLeft);
                exprTypes(expr.exprRight);
                checkInitialization(expr.exprLeft);
                checkInitialization(expr.exprRight);
                if(expr.exprLeft.countedType.varType == UNDEFINED || expr.exprLeft.countedType.varType == VOID){
                    throw new IllegalArgumentException("Неверный тип (ID: " + expr.exprLeft.id + ") для заполнения массива (ID: " + expr.id + ")");
                }
                expr.defineTypeOfExpr();
            }

            case BLOCK -> {
                if(expr.stmtList!=null){
                    expr.stmtList.list.forEach(this::stmtTypes);
                    StatementNode lastStmt = expr.stmtList.list.get(expr.stmtList.list.size()-1);
                    if(lastStmt.type==StatementType.EXPRESSION){
                        expr.countedType = lastStmt.expr.countedType;
                    }
                }
                else {
                    expr.countedType = new TypeNode(UNDEFINED);
                }

            }

            case CONTINUE -> {
                if(insideLoop==0){
                    throw new IllegalArgumentException("Непредвиденный continue вне цикла (ID: " + expr.id + ")");
                }
            }
            default -> expr.defineTypeOfExpr();
        }
    }

    private void checkInitialization(ExpressionNode expr){
        if(expr==null){
            return;
        }
        if(expr.type==ExpressionType.ID && expr.variableTableItem()!= null && !expr.variableTableItem().isInitialized()){
            throw new IllegalArgumentException("Неинициализированная переменная " + expr.name + "(ID: " + expr.id + ")");
        }
    }

    private void checkMutabilityAsgn(ExpressionNode exprLeft){
        if(exprLeft==null || exprLeft.type!=ExpressionType.ID){
            return;
        }
        if(exprLeft.variableTableItem()!=null && exprLeft.variableTableItem().isMut()==Mutable.NOT_MUT) {
            throw new IllegalArgumentException("Невозможно присвоение не модифицируемому выражению(ID: " + exprLeft.id + ")");
        }
    }


    private void declarationTypes(DeclarationStatementNode decl) {
        switch (decl.type) {
            case FUNCTION -> functionTypes(decl.functionItem);
            case ENUM -> {
                //todo хз че в енаме проверить можно
            }
            case CONST_STMT -> constStmtTypes(decl.constStmtItem);
            case STRUCT -> structTypes(decl.structItem);
            case TRAIT -> traitTypes(decl.traitItem);
            case IMPL -> implTypes(decl.implItem);
        }
    }

    private void traitTypes(TraitNode trait){
        if(trait.associatedItemList!=null){
            for (AssociatedItemNode item : trait.associatedItemList.list){
                if(item.fun!=null){
                    functionTypes(item.fun);
                }else if(item.constStmt!=null){
                    constStmtTypes(item.constStmt);
                }
            }
        }
    }

    private void functionTypes(FunctionNode function) {
        if(function.body!=null){
            if (function.body.stmtList != null) {
                function.body.stmtList.list.forEach(this::stmtTypes);
            }
            functionReturnCheck(function);
        }
    }

    private void structTypes(StructNode struct){
        if(struct.structList!=null){
            for(StructItemNode structItem: struct.structList.list){
                if(!checkClassExists(structItem.type)){
                    throw new IllegalArgumentException("Неизвестный тип " + structItem.type.getName() + " для поля " + structItem.name + " при объявлении структуры " + struct.name + " (ID: " + structItem.id + ")");
                }
            }
        }
    }

    private boolean checkClassExists(TypeNode type){
        if(type.varType==ID && tables.tableByName(type.name)==null){
            return false;
        }
        else if(type.varType==ARRAY) {
            return checkClassExists(type.typeArr);
        }
        else {
            return true;
        }
    }

    private void implTypes(ImplNode impl){
        if(impl.associatedItemList!=null){
            for (AssociatedItemNode item : impl.associatedItemList.list){
                if(item.fun!=null){
                    functionTypes(item.fun);
                }else if(item.constStmt!=null){
                    constStmtTypes(item.constStmt);
                }
            }
        }
    }

    private void constStmtTypes(ConstStatementNode constStmt){
        exprTypes(constStmt.expr);
        if(!constStmt.expr.countedType.equals(constStmt.type)){
            throw new IllegalArgumentException("При присвоении константе " + constStmt.name + " (ID: " + constStmt.id + ") значения ожидался тип " + constStmt.type.getName() + ", реальный - " + constStmt.expr.countedType.getName());
        }
    }

    //---------------------- Проверка return в функции -----------------------------
    private void functionReturnCheck(FunctionNode function){
        if (function.returnType.varType != VOID) {
            if (function.body.stmtList == null) {
                throw new IllegalArgumentException("Пустое тело у функции " + function.name + ", но ожидалось возвращаемое значение типа " + function.returnType.getName());
            } else if (!bodyHasReturn(function, function.body)) {
                throw new IllegalArgumentException("У функции " + function.name + "(ID: " + function.id + ") нет явного возвращаемого значения");
            }
        }
        bodyReturnValidation(function, function.body);
    }

    private boolean bodyHasReturn(FunctionNode function, ExpressionNode body){
        if(body.stmtList!=null){
            for (StatementNode stmt : body.stmtList.list){
                if(stmt.type == StatementType.EXPRESSION){
                    switch (stmt.expr.type){
                        case RETURN -> {
                            if(function.returnType.varType == VOID){
                                if(stmt.expr.exprLeft!=null){
                                    throw new IllegalArgumentException("Узел (ID: " + stmt.expr.id + ") возвращает тип " + stmt.expr.exprLeft.countedType.getName() + ", когда функция " + function.name + " должна возвращать тип " + function.returnType.getName());
                                }else {
                                    return true;
                                }
                            }
                            else {
                                if(stmt.expr.exprLeft!=null){
                                    if(stmt.expr.exprLeft.countedType.equals(function.returnType)){
                                        return true;
                                    }else {
                                        throw new IllegalArgumentException("Узел (ID: " + stmt.expr.id + ") возвращает тип " + stmt.expr.exprLeft.countedType.getName() + ", когда функция " + function.name + " должна возвращать тип " + function.returnType.getName());
                                    }
                                }else {
                                    throw new IllegalArgumentException("Узел (ID: " + stmt.expr.id + ") возвращает пустое значение, когда функция " + function.name + " должна возвращать тип " + function.returnType.getName());
                                }
                            }
                        }
                        case IF -> {
                            if(stmt.expr.elseBody!=null && bodyHasReturn(function, stmt.expr.body) && bodyHasReturn(function, stmt.expr.elseBody)){
                                return true;
                            }
                        }
                    }
                }
            }
            StatementNode lastStmt = body.stmtList.list.get(body.stmtList.list.size()-1);
            if(lastStmt.type == StatementType.EXPRESSION && lastStmt.expr.countedType!=null && lastStmt.expr.countedType.equals(function.returnType)){
                lastStmt.expr.isReturn = true;
                return true;
            }
        }
        return false;
    }

    private void bodyReturnValidation(FunctionNode function, ExpressionNode body){
        if(body.stmtList!=null) {
            for (StatementNode stmt : body.stmtList.list) {
                if (stmt.type == StatementType.EXPRESSION) {
                    exprReturnValidation(function, stmt.expr);
                }
            }
        }
    }

    private void exprReturnValidation(FunctionNode function, ExpressionNode expr){
        switch (expr.type){
            case RETURN -> {
                if(function.returnType.varType == VOID){
                    if(expr.exprLeft!=null){
                        throw new IllegalArgumentException("Узел (ID: " + expr.id + ") возвращает тип " + expr.exprLeft.countedType.getName() + ", когда функция " + function.name + " должна возвращать тип " + function.returnType.getName());
                    }
                }
                else {
                    if(!expr.exprLeft.countedType.equals(function.returnType)){
                        throw new IllegalArgumentException("Узел (ID: " + expr.id + ") возвращает тип " + expr.exprLeft.countedType.getName() + ", когда функция " + function.name + " должна возвращать тип " + function.returnType.getName());
                    }
                }
            }
            case LOOP_FOR, LOOP_WHILE, LOOP -> bodyReturnValidation(function, expr.body);
            case IF -> {
                bodyReturnValidation(function, expr.body);
                if(expr.elseBody!=null){
                    bodyReturnValidation(function, expr.elseBody);
                }
            }
        }
    }
}
