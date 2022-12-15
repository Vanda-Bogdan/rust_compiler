package main.semantic;


import main.nodes.conststmt.ConstStatementNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.struct.StructItemNode;

import java.util.HashMap;

public class FieldTable {

    HashMap<String, FieldTableItem> items = new HashMap<>();

    public void add(ConstStatementNode constStmt){
        items.put(constStmt.name, new FieldTableItem(constStmt.type.getName(), true, constStmt.expr));
    }

    public void add(StructItemNode structItem){
        items.put(structItem.name, new FieldTableItem(structItem.type.getName(), false, null));
    }

    public record FieldTableItem(String type, boolean isConst, ExpressionNode expr) {
    }
}
