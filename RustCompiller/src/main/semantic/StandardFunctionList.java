package main.semantic;

import main.nodes.Mutable;
import main.nodes.TypeNode;
import main.nodes.VarType;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionParamListNode;
import main.nodes.function.FunctionParamNode;
import main.nodes.function.FunctionType;

import java.util.ArrayList;
import java.util.HashMap;

public class StandardFunctionList {

    public StandardFunctionList(){
        printlnCreate();
        printlnI32Create();
        printlnF64Create();
        printlnCharCreate();
        printlnBoolCreate();

        readlnCreate();
        readlnI32Create();
        readlnF64Create();
    }

    //--------------------------- Список стандартных функций ----------------------
    private HashMap<String, MethodTable.MethodTableItem> standardFunctionsList = new HashMap<>();

    public boolean standardFunctionExists(String name){
        return standardFunctionsList.get(name) != null;
    }

    public TypeNode standardFunctionReturnType(String name){
        return standardFunctionsList.get(name).returnType();
    }

    public MethodTable.MethodTableItem method(String name){
        return standardFunctionsList.get(name);
    }

    private void printlnI32Create(){
        FunctionParamNode firstParam = new FunctionParamNode("format_string", Mutable.NOT_MUT, new TypeNode(VarType.STRING));
        FunctionParamNode secondParam = new FunctionParamNode("int_value", Mutable.NOT_MUT, new TypeNode(VarType.INT));
        ArrayList<FunctionParamNode> list = new ArrayList<>();
        list.add(firstParam);
        list.add(secondParam);
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, list);
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.VOID), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("println_i32", methodTableItem);
    }

    private void printlnF64Create(){
        FunctionParamNode firstParam = new FunctionParamNode("format_string", Mutable.NOT_MUT, new TypeNode(VarType.STRING));
        FunctionParamNode secondParam = new FunctionParamNode("float_value", Mutable.NOT_MUT, new TypeNode(VarType.FLOAT));
        ArrayList<FunctionParamNode> list = new ArrayList<>();
        list.add(firstParam);
        list.add(secondParam);
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, list);
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.VOID), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("println_f64", methodTableItem);
    }

    private void printlnCharCreate(){
        FunctionParamNode firstParam = new FunctionParamNode("format_string", Mutable.NOT_MUT, new TypeNode(VarType.STRING));
        FunctionParamNode secondParam = new FunctionParamNode("char_value", Mutable.NOT_MUT, new TypeNode(VarType.CHAR));
        ArrayList<FunctionParamNode> list = new ArrayList<>();
        list.add(firstParam);
        list.add(secondParam);
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, list);
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.VOID), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("println_char", methodTableItem);
    }

    private void printlnBoolCreate(){
        FunctionParamNode firstParam = new FunctionParamNode("format_string", Mutable.NOT_MUT, new TypeNode(VarType.STRING));
        FunctionParamNode secondParam = new FunctionParamNode("bool_value", Mutable.NOT_MUT, new TypeNode(VarType.BOOL));
        ArrayList<FunctionParamNode> list = new ArrayList<>();
        list.add(firstParam);
        list.add(secondParam);
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, list);
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.VOID), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("println_bool", methodTableItem);
    }

    private void printlnCreate(){
        FunctionParamNode firstParam = new FunctionParamNode("format_string", Mutable.NOT_MUT, new TypeNode(VarType.STRING));
        ArrayList<FunctionParamNode> list = new ArrayList<>();
        list.add(firstParam);
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, list);
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.VOID), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("println", methodTableItem);
    }

    private void readlnCreate(){
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, new ArrayList<FunctionParamNode>());
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.STRING), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("readln", methodTableItem);
    }

    private void readlnI32Create(){
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, new ArrayList<FunctionParamNode>());
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.INT), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("readln_i32", methodTableItem);
    }

    private void readlnF64Create(){
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, new ArrayList<FunctionParamNode>());
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.FLOAT), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("readln_f64", methodTableItem);
    }
}
