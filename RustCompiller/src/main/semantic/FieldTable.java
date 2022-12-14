package main.semantic;


import main.nodes.conststmt.ConstStatementNode;
import main.nodes.struct.StructItemNode;

import java.util.ArrayList;

public class FieldTable {

    ArrayList<FieldTableItem> items = new ArrayList<>();

    public void add(ConstStatementNode constStmt){
        items.add(new FieldTableItem(constStmt.name, constStmt.type.getName(), true));
    }

    public void add(StructItemNode structItem){
        items.add(new FieldTableItem(structItem.name, structItem.type.getName(), false));
    }

    public record FieldTableItem(String name, String type, boolean isConst) {
    }
}
