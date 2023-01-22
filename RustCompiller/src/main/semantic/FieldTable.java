package main.semantic;


import main.nodes.TypeNode;
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

    public boolean contains(String name){
        return items.containsKey(name);
    }

    private int amountNotConst = 0;
    public int amountNotConst(){
        return amountNotConst;
    }

    private int amountConst = 0;
    public int amountConst(){
        return amountConst;
    }

    public void add(ConstStatementNode constStmt){
        items.put(constStmt.name, new FieldTableItem(constStmt.type, true, constStmt.expr));
        amountConst++;
    }

    public void add(StructItemNode structItem){
        items.put(structItem.name, new FieldTableItem(structItem.type, false, null));
        amountNotConst++;
    }

    public void add(EnumItemNode enumItem, String name){
        items.put(enumItem.name, new FieldTableItem(new TypeNode(name), false, enumItem.expr));
        amountNotConst++;
    }

    public void add(String name, FieldTableItem item){
        items.put(name, item);
    }

    public record FieldTableItem(TypeNode type, boolean isConst, ExpressionNode expr) {
    }
}
