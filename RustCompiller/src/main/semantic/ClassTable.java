package main.semantic;

import main.nodes.conststmt.ConstStatementNode;
import main.nodes.enumm.EnumItemNode;
import main.nodes.function.FunctionNode;
import main.nodes.struct.StructItemNode;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public class ClassTable {

    String name;
    private Tables tables;

    public ClassTable(String name, Tables tables) {
        this.name = name;
    }



    //------------------------------------------Constant Table-------------------------------------------------------
    private ConstantTable constantTable = new ConstantTable();

    public int getConstNumber(Constant constant){
        return constantTable.getConstNumber(constant);
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
    private FieldTable fieldTable = new FieldTable();

    public FieldTable fields(){
        return fieldTable;
    }

    public void addToFieldTable(ConstStatementNode constStmt){
        fieldTable.add(constStmt);
    }

    public void addToFieldTable(StructItemNode structItem){
        fieldTable.add(structItem);
    }

    public void addToFieldTable(EnumItemNode enumItem, String name){
        fieldTable.add(enumItem, name);
    }

    public void addToFieldTable(String name, FieldTable.FieldTableItem item) {
        fieldTable.add(name, item);
    }

    public boolean containsField(String name) { return fieldTable.contains(name); }

    //------------------------------------------MethodTable------------------------------------------
    private MethodTable methodTable = new MethodTable();

    public void addToMethodTable(FunctionNode funcNode){
        methodTable.add(funcNode, null, tables);
    }

    public void addToMethodTable(FunctionNode funcNode, FieldTable fields){
        methodTable.add(funcNode, fields, tables);
    }

    public void addToMethodTable(String name, MethodTable.MethodTableItem item){
        methodTable.add(name, item);
    }

    public boolean containsMethod(String name){
        return methodTable.items.containsKey(name);
    }

    public void outputToFile() throws IOException {
        PrintWriter writer = new PrintWriter(new File(name + ".csv"));
        writer.write("№ константы,Тип константы,Значение константы\n");
        AtomicInteger i = new AtomicInteger();
        constantTable.items.forEach(
                (item) -> {
                    if (!item.utf8().isEmpty()) {
                        writer.write(i.getAndIncrement() + "," + item.type() + "," + item.utf8() + "\n");
                    }
                    else if (item.firstVal()!=-1 && item.secondVal()!=-1){
                        writer.write(i.getAndIncrement() + "," + item.type() + "," + item.firstVal() + " " + item.secondVal() + "\n");
                    }
                    else if(item.firstVal()!=-1){
                        writer.write(i.getAndIncrement() + "," + item.type() + "," + item.firstVal() + "\n");
                    }
                    else {
                        throw new IllegalArgumentException("Некорректное построение таблицы констант для класса " + name);
                    }
                }
        );
        writer.close();
    }
}
