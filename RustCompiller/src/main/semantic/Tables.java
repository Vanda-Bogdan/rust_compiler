package main.semantic;

import main.nodes.ProgramNode;
import main.nodes.TypeNode;
import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.declstmt.DeclarationStatementType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;
import main.nodes.struct.StructListNode;
import main.nodes.trait.TraitNode;
import main.treeprint.Tree;

import java.util.ArrayList;
import java.util.HashMap;

public class Tables {

    private ClassTable currentTable = null;

    private HashMap<String, ClassTable> tables = new HashMap<String, ClassTable>();

    private TraitTable traitTable = new TraitTable();

    public ClassTable tableByName(String name){
        return tables.get(name);
    }

    private ClassTable createTable(String name) {
        ClassTable table = new ClassTable(name);
        tables.put(name, table);
        currentTable = table;
        return table;
    }

    public void createTables(Tree tree) {

        createTable("Main");
        stmtListTrait(tree.prg.stmtList);
        stmtListClasses(tree.prg.stmtList);
    }

    //----------------------------------------Сбор всех трейтов-----------------------------------------
    private void stmtListTrait(StatementListNode stmtList){
        stmtList.list.forEach(this::stmtTrait);
    }

    private void stmtTrait(StatementNode stmt) {
        if (stmt.type == StatementType.DECLARATION) {
            declStmtTrait(stmt.declarationStmt);
        }
    }

    private void declStmtTrait(DeclarationStatementNode declStmt){
        if (declStmt.type == DeclarationStatementType.TRAIT) {
            traitTable.add(declStmt.traitItem);
        }
    }


    //-----------------------------------------Обход дерева---------------------------------------------
    private void stmtListClasses(StatementListNode stmtList) {
        stmtList.list.forEach(this::stmtClasses);
    }

    private void stmtClasses(StatementNode stmt) {
        switch (stmt.type) {
            //case EXPRESSION -> exprParse(stmt.expr);
            case LET -> letStmtClasses(stmt.letStmt);
            case DECLARATION -> declStmtClasses(stmt.declarationStmt);
        }
    }

    private void declStmtClasses(DeclarationStatementNode declStmt){
        switch (declStmt.type) {
            case STRUCT -> {

            }

            case IMPL -> {

            }
        }
    }





    private void letStmtClasses(LetStatementNode letStmt) {

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
