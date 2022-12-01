package main.nodes.function;

import main.nodes.TypeNode;
import main.nodes.expression.ExpressionNode;

public class FunctionNode {
    public int id;
    public String name;
    public TypeNode returnType;
    public FunctionParamListNode paramList;
    public ExpressionNode body;
}
