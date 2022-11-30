package main.nodes.trait;

import main.nodes.conststmt.ConstStatementNode;
import main.nodes.function.FunctionNode;
import main.nodes.Visibility;

public class AssociatedItemNode {
    public int id;
    public FunctionNode fun;
    public Visibility visibility;
    public ConstStatementNode constStmt;
}
