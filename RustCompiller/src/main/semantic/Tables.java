package main.semantic;

import main.nodes.ProgramNode;
import main.nodes.TypeNode;
import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.nodes.struct.StructListNode;
import main.treeprint.Tree;

import java.util.ArrayList;
import java.util.HashMap;

public class Tables {

    public ClassTable currentTable = null;

    private HashMap<String, ClassTable> tables = new HashMap<String, ClassTable>();

    public ClassTable tableByName(String name){
        return tables.get(name);
    }

    public ClassTable createTable(String name){
        ClassTable table = new ClassTable(name);
        tables.put(name, table);
        currentTable = table;
        return table;
    }

    private void createTables(Tree tree) {

        createTable("Main");
        stmtListParse(tree.prg.stmtList);
    }

    //Обход дерева
    private void stmtListParse(StatementListNode stmtList) {
        stmtList.list.forEach(Tables::stmtParse);
    }

    private void stmtParse(StatementNode stmt) {
        switch (stmt.type){
            //case EXPRESSION -> exprParse(stmt.expr);
            case LET -> letStmtParse(stmt.letStmt);
            case DECLARATION -> declStmtParse(stmt.declarationStmt);
        }
    }

    private void declStmtParse(DeclarationStatementNode declStmt){
        switch (declStmt.type){
            case STRUCT -> {

            }

            case IMPL -> {

            }
        }
    }

    private void letStmtParse(LetStatementNode letStmt) {

    }

    /*private boolean searchByName(String name) {
        for (ClassTable element : tables) {
            if (element.name == name) {
                return true;
            }
        }
        return false;
    }*/

    private static String typeParse(TypeNode type) {
        switch (type.varType) {
            case INT -> {
                return "I";
            }
            case CHAR -> {
                return "C";
            }
            case STRING -> {
                return "S";
            }
            case FLOAT -> {
                return "F";
            }
            case BOOL -> {
                return "B";
            }
            case ID -> {
                return type.name;
            }
            case ARRAY -> {
                TypeNode tArr = type.typeArr;
                while (tArr.typeArr != null) {
                    tArr = tArr.typeArr;
                }
                return typeParse(tArr);
            }
            default -> {
                return null;
            }
        }
    }
}
