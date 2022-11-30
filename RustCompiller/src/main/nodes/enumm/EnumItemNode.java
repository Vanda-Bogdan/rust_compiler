package main.nodes.enumm;

import main.nodes.struct.StructListNode;
import main.nodes.Visibility;
import main.nodes.expression.ExpressionNode;

public class EnumItemNode {
    public int id;
    public Visibility visibility;
    public String name;
    public ExpressionNode expr;
    public StructListNode structList;
}