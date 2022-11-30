package main.nodes.letstmt;

import main.nodes.Mutable;
import main.nodes.TypeNode;
import main.nodes.expression.ExpressionNode;

public class LetStatementNode {
    public int id;
    public String name;
    public Mutable mut;
    public TypeNode type;
    public ExpressionNode expr;
}
