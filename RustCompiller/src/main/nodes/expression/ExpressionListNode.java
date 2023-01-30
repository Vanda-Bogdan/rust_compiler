package main.nodes.expression;

import java.util.ArrayList;
import java.util.Objects;

public class ExpressionListNode {
    public int id;
    public ArrayList<ExpressionNode> list = new ArrayList<>();

    public ExpressionNode getStructFieldExprByName(String name){
        for (ExpressionNode expr: list) {
            if(Objects.equals(expr.name, name)){
                return expr;
            }
        }
        return null;
    }
}
