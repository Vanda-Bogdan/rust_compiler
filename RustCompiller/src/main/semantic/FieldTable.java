package main.semantic;


import main.nodes.conststmt.ConstStatementNode;
import main.nodes.enumm.EnumItemNode;
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

    public void add(EnumItemNode enumItem, String name){
        items.put(enumItem.name, new FieldTableItem(name, false, enumItem.expr));
    }

    public void add(String name, FieldTableItem item){
        items.put(name, item);
    }

    public record FieldTableItem(String type, boolean isConst, ExpressionNode expr) {
    }
}
