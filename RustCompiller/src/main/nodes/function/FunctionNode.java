package main.nodes.function;

import main.nodes.TypeNode;
import main.nodes.VarType;
import main.nodes.expression.ExpressionNode;

public class FunctionNode {
    public int id;
    public String name;
    public TypeNode returnType;
    public FunctionParamListNode paramList;
    public ExpressionNode body;

    public String funcTypeForTable(){
        String result = "(";
        if(paramList!=null){
            for(FunctionParamNode param : paramList.list){
                result+=param.type.getNameForTable();
            }
        }
        result+= ")" + returnType.getNameForTable();
        return result;
    }
}
