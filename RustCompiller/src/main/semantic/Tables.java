package main.semantic;

import main.nodes.ProgramNode;
import main.nodes.TypeNode;
import main.nodes.letstmt.LetStatementNode;

import java.util.ArrayList;

import static main.semantic.Constant.*;

public class Tables {

    public ArrayList<Table> tables = new ArrayList<>();
    public Table currentTable = null;

    public void create(ProgramNode root) {

        currentTable = new Table("Main");



    }

    private void letStmtParse(LetStatementNode letStmt) {

    }

    private boolean searchByName(String name) {
        for (Table element : tables) {
            if (element.name == name) {
                return true;
            }
        }
        return false;
    }

    private String typeParse(TypeNode type) {
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
