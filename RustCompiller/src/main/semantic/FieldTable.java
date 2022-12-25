package main.semantic;


import main.nodes.conststmt.ConstStatementNode;
import main.nodes.enumm.EnumItemNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.struct.StructItemNode;

import java.util.ArrayList;
import java.util.HashMap;

public class FieldTable {

    public HashMap<String, FieldTableItem> items = new HashMap<>();

    public FieldTableItem get(String name){
        return items.get(name);
    }

    public ArrayList<String> fields(){
        return new ArrayList<>(items.keySet());
    }

    public boolean contains(String name){
        return items.containsKey(name);
    }

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
