package main.nodes.declstmt;

import main.nodes.conststmt.ConstStatementNode;
import main.nodes.enumm.EnumNode;
import main.nodes.function.FunctionNode;
import main.nodes.impl.ImplNode;
import main.nodes.struct.StructNode;
import main.nodes.trait.TraitNode;

public class DeclarationStatementNode {
    public int id;
    public DeclarationStatementType type;
    public StructNode structItem;
    public FunctionNode functionItem;
    public EnumNode enumItem;
    public ConstStatementNode constStmtItem;
    public TraitNode traitItem;
    public ImplNode implItem;
}
