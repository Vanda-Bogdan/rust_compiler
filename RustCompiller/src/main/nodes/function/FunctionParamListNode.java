package main.nodes.function;

import java.util.ArrayList;

public class FunctionParamListNode {
    public int id;
    public FunctionType type;
    public ArrayList<FunctionParamNode> list = new ArrayList<>();

    public FunctionParamListNode(){}

    public FunctionParamListNode(FunctionType type, ArrayList<FunctionParamNode> list){
        this.type = type;
        this.list = list;
    }
}
