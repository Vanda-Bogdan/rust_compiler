package main.nodes;

import main.nodes.expression.ExpressionNode;

public class TypeNode {
    public int id;
    public VarType varType;
    public String name;
    public TypeNode typeArr;
    public ExpressionNode exprArr;

    public String getName() {
        if(varType == VarType.ID){
            return name;
        }
        else if(varType != VarType.ARRAY){
            return varType.toString();
        }
        else {
            return "[" + typeArr.getName() + "; " + exprArr.anInt + "]";
        }
    }
}
