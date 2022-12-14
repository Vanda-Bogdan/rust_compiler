package main.semantic;

import main.nodes.conststmt.ConstStatementNode;
import main.nodes.function.FunctionNode;
import main.nodes.struct.StructItemNode;

public class ClassTable {

    String name;
    public ClassTable(String name) {
        this.name = name;
    }

    //------------------------------------------Constant Table-------------------------------------------------------
    private ConstantTable constantTable = new ConstantTable();

    public int getConstNumber(Constant constant, String utf8){
        return constantTable.getConstNumber(constant, utf8);
    }

    public int constantAdd(Constant constant, int num1){
        return constantTable.add(constant, num1);
    }

    public int constantAdd(Constant constant, int num1, int num2){
        return constantTable.add(constant, num1, num2);
    }

    public int constantAdd(Constant constant, String utf8){
        return constantTable.add(constant, utf8);
    }


    public boolean constantContains(Constant constant, int num1){
        return constantTable.contains(constant, num1);
    }

    public boolean constantContains(Constant constant, int num1, int num2){
        return constantTable.contains(constant, num1, num2);
    }

    public boolean constantContains(Constant constant, String utf8){
        return constantTable.contains(constant, utf8);
    }

    //------------------------------------------Field Table------------------------------------------
    private FieldTable fieldTable;

    public void fieldsAdd(ConstStatementNode constStmt){
        fieldTable.add(constStmt);
    }

    public void fieldsAdd(StructItemNode structItem){
        fieldTable.add(structItem);
    }

    //------------------------------------------MethodTable------------------------------------------
    private MethodTable methodTable;

    public void addToMethodTable(FunctionNode funcNode){
        methodTable.add(funcNode);
    }

    public boolean containsMethod(String name){
        return methodTable.items.containsKey(name);
    }
}
