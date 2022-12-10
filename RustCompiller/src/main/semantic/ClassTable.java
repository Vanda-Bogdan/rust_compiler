package main.semantic;

public class ClassTable {

    String name;
    public ClassTable(String name) {
        this.name = name;
    }

    //Constant Table
    private ConstantTable constantTable = new ConstantTable();


    public void constantAdd(Constant constant, int num1){
        constantTable.add(constant, num1);
    }

    public void constantAdd(Constant constant, int num1, int num2){
        constantTable.add(constant, num1, num2);
    }

    public void constantAdd(Constant constant, String utf8){
        constantTable.add(constant, utf8);
    }


    public boolean constantContains(Constant constant, int num1){
        return constantTable.exists(constant, num1);
    }

    public boolean constantContains(Constant constant, int num1, int num2){
        return constantTable.exists(constant, num1, num2);
    }

    public boolean constantContains(Constant constant, String utf8){
        return constantTable.exists(constant, utf8);
    }

    //Field Table
    private FieldTable fieldTable;

    //MethodTable
    private MethodTable methodTable;

}
