package main.semantic;

import main.nodes.conststmt.ConstStatementNode;
import main.nodes.enumm.EnumItemNode;
import main.nodes.function.FunctionNode;
import main.nodes.struct.StructItemNode;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.concurrent.atomic.AtomicInteger;

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
    private FieldTable fieldTable = new FieldTable();

    public void addToFieldTable(ConstStatementNode constStmt){
        fieldTable.add(constStmt);
    }

    public void addToFieldTable(StructItemNode structItem){
        fieldTable.add(structItem);
    }

    public void addToFieldTable(EnumItemNode enumItem, String name){
        fieldTable.add(enumItem, name);
    }

    public boolean containsField(String name) { return fieldTable.items.containsKey(name); }

    //------------------------------------------MethodTable------------------------------------------
    private MethodTable methodTable = new MethodTable();

    public void addToMethodTable(FunctionNode funcNode){
        methodTable.add(funcNode);
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
                    if (item.utf8() != null) {
                        writer.write(i.getAndIncrement() + "," + item.type() + "," + item.utf8() + "\n");
                    }
                    else if (item.firstVal()!=-1 && item.secondVal()!=-1){

                        writer.write(i.getAndIncrement() + "," + item.type() + "," + item.firstVal() + " " + item.secondVal() + "\n");
                    }
                    else if(item.firstVal()!=-1){
                        writer.write(i.getAndIncrement() + "," + item.type() + "," + item.firstVal() + "\n");
                    }
                }
        );
        writer.close();
    }
}
