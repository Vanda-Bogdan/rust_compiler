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

    private void printlnCreate(){
        FunctionParamNode firstParam = new FunctionParamNode("format_string", Mutable.NOT_MUT, new TypeNode(VarType.STRING));
        ArrayList<FunctionParamNode> list = new ArrayList<>();
        list.add(firstParam);
        FunctionParamListNode params = new FunctionParamListNode(FunctionType.ASSOCIATED, list);
        MethodTable.MethodTableItem methodTableItem = new MethodTable.MethodTableItem(new TypeNode(VarType.VOID), new VariableTable(), true, FunctionType.ASSOCIATED, params, new ExpressionNode());

        standardFunctionsList.put("println", methodTableItem);
    }
}
