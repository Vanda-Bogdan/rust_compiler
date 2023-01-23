package main.nodes.function;

import main.nodes.Mutable;
import main.nodes.TypeNode;

public class FunctionParamNode {
    public int id;
    public String name;
    public Mutable mut;
    public TypeNode type;

    public FunctionParamNode(String name, Mutable mut, TypeNode type){
        this.name = name;
        this.mut = mut;
        this.type = type;
    }

    public FunctionParamNode(){}
}
