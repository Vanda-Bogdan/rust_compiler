package main.semantic;

import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionParamListNode;

import java.util.ArrayList;

public class MethodTable {

    public ArrayList<MethodTableItem> items = new ArrayList<>();

    public void add(String name, String returnType, FunctionNode funcNode) {

    }

    private record MethodTableItem(String name, String returnType, VariableTable variableTable, boolean hasBody) {
    }
}
