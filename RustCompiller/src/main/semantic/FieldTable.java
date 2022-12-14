package main.semantic;


import main.nodes.conststmt.ConstStatementNode;
import main.nodes.struct.StructItemNode;

import java.util.ArrayList;
import java.util.HashMap;

public class FieldTable {

    HashMap<String, FieldTableItem> items = new HashMap<>();

    public void add(ConstStatementNode constStmt){
        items.put(constStmt.name, new FieldTableItem(constStmt.type.getName(), true));
    }

    public void add(StructItemNode structItem){
        items.put(structItem.name, new FieldTableItem(structItem.type.getName(), false));
    }

    public record FieldTableItem(String type, boolean isConst) {
    }
}
