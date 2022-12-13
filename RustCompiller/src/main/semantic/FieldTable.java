package main.semantic;

import main.nodes.Visibility;
import main.nodes.conststmt.ConstStatementNode;
import main.nodes.struct.StructItemNode;

import java.util.ArrayList;

public class FieldTable {

    ArrayList<FieldTableItem> items = new ArrayList<>();

    public void add(ConstStatementNode constStmt, Visibility visibility){
        items.add(new FieldTableItem(visibility, constStmt.name, constStmt.type.getName(), true));
    }

    public void add(StructItemNode structItem, Visibility visibility){
        items.add(new FieldTableItem(visibility, structItem.name, structItem.type.getName(), false));
    }

    public record FieldTableItem(Visibility visibility, String name, String type, boolean isConst) {
    }
}
