package main.nodes.stmt;

import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.letstmt.LetStatementNode;

public class StatementNode {
    public int id;
    public StatementType type;
    public ExpressionNode expr;
    public DeclarationStatementNode declarationStmt;
    public LetStatementNode letStmt;
}
